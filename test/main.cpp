#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE UnitTest

#include <boost/test/unit_test.hpp>

#include "../include/simpleFastCGIcpp.h"

// just logging something ( --log_level=message )

BOOST_AUTO_TEST_CASE( test000 ) {
   BOOST_TEST_MESSAGE( "\ntest000\n" );
   BOOST_CHECK( true );
}

