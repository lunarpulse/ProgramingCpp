#include <cstdint>
#include <array>
#include <iostream>
#include <math/filters/fir_order_n.h>


const std::array<std::uint16_t, 101U> data =
{
{
250U, 288U, 306U, 301U, 287U, 288U, 312U,
381U, 386U, 371U, 354U, 357U, 381U, 412U,
417U, 390U, 370U, 372U, 392U, 411U, 409U,
347U, 326U, 328U, 343U, 350U, 333U, 296U,
241U, 246U, 258U, 256U, 231U, 190U, 158U,
162U, 176U, 170U, 141U, 106U, 87U, 93U,
132U, 125U, 100U, 77U, 75U, 97U, 129U,
141U, 123U, 113U, 127U, 162U, 198U, 215U,
195U, 197U, 224U, 264U, 297U, 306U, 296U,
293U, 325U, 363U, 386U, 383U, 364U, 352U,
392U, 420U, 427U, 409U, 381U, 368U, 377U,
414U, 403U, 371U, 338U, 324U, 332U, 348U,
322U, 282U, 250U, 240U, 250U
}
};

typedef fir_order_n<17U,
64U,
std::uint16_t,
std::uint32_t> filter_type;
void do_something()
{
filter_type f(data[0U]);
std::cout << f.get_result() << "\n";
std::for_each(
data.begin() + 1U,
data.end(),
[&f](const std::uint16_t& s)
{
f.new_sample
<-2, -2, -2, -1, 3, 9, 15, 20, 24,
24, 20, 15, 9, 3, -1, -2, -2, -2>(s);
std::cout << f.get_result() << "\n";
});
}

typedef fir_order_n<5U> filter_type;
void do_something()
{
filter_type f1(data[0U]);
filter_type f2(f1.get_result());
std::cout << f2.get_result() << std::endl;
std::for_each(
data.begin() + 1U,
data.end(),
[&f1, &f2](const std::uint16_t& s)
{
f1.new_sample<5, 5, 6, 6, 5, 5>(s);
filter_type::result_type r = f1.get_result();
f2.new_sample<5, 5, 6, 6, 5, 5>(r);
std::cout << f2.get_result() << std::endl;
});
}

#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <string>





int main()
{
const std::regex rx(
+
+
+
+
std::string("([_0-9a-zA-Z]+)")
std::string("[[:space:]]+")
std::string("([0-9a-fA-F]+)")
std::string("[[:space:]]+")
std::string("([0-9]+)"));
const std::string str("_My_Variable123 03FFB004 4");
std::match_results<std::string::const_iterator> mr;
if(std::regex_match(str, mr, rx))
{
std::copy(mr.begin(),
mr.end(),
std::ostream_iterator
<std::string>(std::cout, "\n"));
}
}