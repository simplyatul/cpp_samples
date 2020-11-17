# cpp_samples

g++ thread_1.cpp -lboost_thread -lpthread


if USE_BOOST is enabled then
$ g++ thread_2.cpp -lboost_thread -lpthread

else

$ g++ thread_2.cpp -lpthread

g++ thread_3.cpp -lboost_thread -lpthread -lboost_chrono
