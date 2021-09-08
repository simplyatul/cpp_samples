/*
 * Ref/Credits: https://www.boost.org/doc/libs/1_61_0/doc/html/circular_buffer/examples.html

*/

#include <boost/circular_buffer.hpp>
#include <numeric>
#include <assert.h>
#include <iostream>

using namespace std;

int main(int /*argc*/, char* /*argv*/[])
{
   // Create a circular buffer of capacity 3.
   boost::circular_buffer<uint8_t> cb(3);
   assert(cb.capacity() == 3);
   // Check is empty.
   assert(cb.size() == 0);
   assert(cb.empty());

   // Insert some elements into the circular buffer.
   cb.push_back(5);
   cb.push_back(2);

   // Assertions to check push_backs have expected effect.
   assert(cb[0] == 5);
   assert(cb[1] == 2);
   assert(!cb.full());
   assert(cb.size() == 2);
   assert(cb.capacity() == 3);

   // Insert some other elements.
   cb.push_back(3);
   cb.push_back(0xb);

   // Evaluate the sum of all elements.
   int sum = std::accumulate(cb.begin(), cb.end(), 0);
   std::cout << "sum " << sum << std::endl;
   // Assertions to check state.
   assert(sum == 9);
   assert(cb[0] == 2);
   assert(cb[1] == 3);
   assert(cb[2] == 4);
   assert(*cb.begin() == 2);
   assert(cb.front() == 2);
   assert(cb.back() == 4);
   assert(cb.full());
   assert(cb.size() == 3);
   assert(cb.capacity() == 3);

   return 0;
}

