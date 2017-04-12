# Simple FastCGI C++

Some proof of concept for mock/test code using [ASIO lib](http://think-async.com/Asio) by [Chris Kohlhoff](https://github.com/chriskohlhoff) and [FastCGI C++ class library](http://althenia.net/fcgicc) by [aaz@q-fu.com](mailto:aaz@q-fu.com).

## NGINX configuration

Don't forget to enable *FastCGI* features and define an ending point to connect to:

       location /dspModule  {
		fastcgi_pass   0.0.0.0:7000;
		fastcgi_connect_timeout 5h;
		fastcgi_read_timeout 5h;

		fastcgi_param  QUERY_STRING       $query_string;
		fastcgi_param  REQUEST_METHOD     $request_method;
		fastcgi_param  CONTENT_TYPE       $content_type;
		fastcgi_param  CONTENT_LENGTH     $content_length;
		fastcgi_param  REQUEST            $request;
		fastcgi_param  REQUEST_BODY       $request_body;
		fastcgi_param  REQUEST_URI        $request_uri;
		fastcgi_param  DOCUMENT_URI       $document_uri;
		fastcgi_param  DOCUMENT_ROOT      $document_root;
		fastcgi_param  SERVER_PROTOCOL    $server_protocol;
		fastcgi_param  REMOTE_ADDR        $remote_addr;
		fastcgi_param  REMOTE_PORT        $remote_port;
		fastcgi_param  SERVER_ADDR        $server_addr;
		fastcgi_param  SERVER_PORT        $server_port;
		fastcgi_param HTTP_REFERER        $http_referer;
		fastcgi_param SCHEME              $scheme;
	}

So the library will try to connect to the port **7000** and the browser to the ending point:

	 http://0.0.0.0/dspModule

