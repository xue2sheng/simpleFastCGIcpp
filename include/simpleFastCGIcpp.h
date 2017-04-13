/** @file simpleFastCGIcpp.h
 * @brief C++ header for simple FastCGI C++  utilities.
 *
 */

#ifndef SIMPLEFASTCGICPP_H
#define SIMPLEFASTCGICPP_H

/**
 * @example
 *
 * Expected request, with main info on POST format, as:
 *
 * @code
 * curl -vvv -H 'Content-Type: application/json' -H 'Accept-Encoding: gzip' "http://XXXXXXXXXX" -d '{"YYY": zzz}'
 * @endcode
 *
 * Nginx configuration for GZIP WITH THE CORRECT ERROR CODE (200) in the response:
 *
 * @code
 * gzip on;
 * gzip_vary on;
 * gzip_proxied any;
 * gzip_comp_level 6;
 * gzip_buffers 16 8k;
 * gzip_http_version 1.1;
 *
 * gzip_types text/plain text/css application/json application/javascript application/x-javascript text/javascript text/xml application/xml application/rss+xml application/atom+xml application/rdf+xml;
 * @endcode
 *
 * Nginx configuration for passing the POST body:
 *
 * @code
 * fastcgi_param  REQUEST_BODY       $request_body;
 * @endcode
 *
 */

#include <map>
#include <string>

///@brief Simple FastCGI C++ Utilities
namespace SimpleFastCGIcpp {

class Wrapper {
public:
	Wrapper();

	virtual ~Wrapper();
private:
  void* pointer_{nullptr}; // in order to avoid dependencies on fcgicc clasess

};

bool helloWorld();

} // namespace

#endif // SIMPLEFASTCGICPP_H
