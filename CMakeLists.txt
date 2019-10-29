cmake_minimum_required(VERSION 3.1.0)
project (OrderBook)
add_executable(order_book OrderBook.cc ClobBasic.hh ClobParser.hh ClobImpl.cc ClobImpl.hh ClobOrder.hh)


