/*
 * run: g++ pre_post_incr_0.cpp
 * prefer pre increment operator. Reasone
 * - It generate less assembly code
 * - most of the time, return value is not used
 * - pre operator returns reference, whereas post operator
 * - returns copy
 */

struct my_int {
    int v;

    constexpr my_int & operator++() {
        ++v;
        return *this;
    }

    constexpr my_int operator++(int) {
        const auto prev = v;
        ++v;
        return *this;
    }

};

int main() {

    my_int k{0};
    // ++i = increment and return new value
    ++k;
    // i++ = increment and return old value
    //k++;
 
    return k.v;
}
