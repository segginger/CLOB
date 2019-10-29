cmake_minimum_required(VERSION 3.1.0)
project (OrderBookTest)

ADD_LIBRARY(boost_unit_test_framework STATIC IMPORTED)
SET_TARGET_PROPERTIES(boost_unit_test_framework PROPERTIES
    IMPORTED_LOCATION /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.a)
add_executable(order_book_test OrderBookTest.cc ../ClobBasic.hh ../ClobParser.hh ../ClobImpl.cc ../ClobImpl.hh ../ClobOrder.hh)
target_link_libraries(order_book_test boost_unit_test_framework)
