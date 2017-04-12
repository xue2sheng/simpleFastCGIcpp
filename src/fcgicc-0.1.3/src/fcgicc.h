/*
 * Copyright 2008, 2009 Andrey Zholos. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * This file is part of the FastCGI C++ Class library (fcgicc) version 0.1,
 * available at http://althenia.net/fcgicc
 */


#ifndef FCGICC_H
#define FCGICC_H

#include <map>
#include <string>
#include <vector>


class FastCGIRequest {
public:
    typedef std::map<std::string, std::string> Params;

    Params params;
    std::string in;
    std::string out;
    std::string err;
};


class FastCGIServer {
public:
    FastCGIServer();
    ~FastCGIServer();

    // called when the parameters and standard input have been receieved
    void request_handler(int (* function)(FastCGIRequest&));
    template<class C>
    void request_handler(C& object, int (C::* function)(FastCGIRequest&)) {
        set_handler(handle_request, new Handler<C>(object, function));
    }

    // called when new data appears on stdin
    void data_handler(int (* function)(FastCGIRequest&));
    template<class C>
    void data_handler(C& object, int (C::* function)(FastCGIRequest&)) {
        set_handler(handle_data, new Handler<C>(object, function));
    }

    // called when the complete request has been received
    void complete_handler(int (* function)(FastCGIRequest&));
    template<class C>
    void complete_handler(C& object, int (C::* function)(FastCGIRequest&)) {
        set_handler(handle_complete, new Handler<C>(object, function));
    }

    void listen(unsigned tcp_port);
    void listen(const std::string& local_path);
    void abandon_files();

    void process(int timeout_ms = -1); // timeout_ms<0 blocks forever
    void process_forever();

protected:
    struct RequestInfo : FastCGIRequest {
        RequestInfo();

        std::string params_buffer;
        bool params_closed;
        bool in_closed;
        int status;
        bool output_closed;

        friend class FastCGIServer;
    };

    typedef unsigned RequestID;
    typedef std::map<RequestID, RequestInfo*> RequestList;
    struct Connection {
        Connection();

        RequestList requests;
        std::string input_buffer;
        std::string output_buffer;
        bool close_responsibility;
        bool close_socket;
    };

    typedef std::map<std::string, std::string> Pairs;

    std::vector<int> listen_sockets;
    std::vector<std::string> listen_unlink;

    std::map<int, Connection*> read_sockets;

    void process_connection_read(Connection&);
    static void process_write_request(Connection&, RequestID, RequestInfo&);
    static void process_connection_write(Connection&);
    static Pairs parse_pairs(const char*, std::string::size_type);
    static void write_pair(std::string& buffer,
        const std::string& key, const std::string&);
    static void write_data(std::string& buffer, RequestID id,
        const std::string& input, unsigned char type);


    struct HandlerBase {
        virtual int operator()(FastCGIRequest&);
    };

    struct StaticHandler : public HandlerBase {
        StaticHandler(int (* p_function)(FastCGIRequest&)) :
            function(p_function) {}
        int operator()(FastCGIRequest& request) {
            return function(request);
        }

        int (* function)(FastCGIRequest&);
    };

    template<class C>
    struct Handler : public HandlerBase {
        Handler(C& p_object, int (C::* p_function)(FastCGIRequest&)) :
            object(p_object), function(p_function) {}
        int operator()(FastCGIRequest& request) {
            return (object.*function)(request);
        }

        C& object;
        int (C::* function)(FastCGIRequest&);
    };

    void set_handler(HandlerBase*&, HandlerBase*);

    HandlerBase* handle_request;
    HandlerBase* handle_data;
    HandlerBase* handle_complete;
};

#endif // !FCGICC_H
