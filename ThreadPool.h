#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

namespace boostThread
{
        typedef std::unique_ptr<boost::asio::io_service::work> asio_worker;
        // the actual thread pool
        class ThreadPool {
        public:
                boost::asio::io_service service; //< the io_service we are wrapping

                ThreadPool(size_t threads) :service(), working(new asio_worker::element_type(service)) {
                        for ( std::size_t i = 0; i < threads; ++i ) {
                                auto worker = boost::bind(&boost::asio::io_service::run, &(this->service));
                                boost::thread *t = new boost::thread(worker);
                                pthread_setname_np(t->native_handle(), __func__);
                                threadpool.add_thread(t);
                        }
                }

                template<class F>
                void enqueue(F f){
                        service.post(f);
                }

                ~ThreadPool() {
                        working.reset(); //allow run() to exit
                        threadpool.join_all();
                        service.stop();
                }

        private:
                asio_worker working;
                boost::thread_group threadpool; //< need to keep track of threads so we can join them
        };
}

#endif

