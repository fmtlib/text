// Warning! This file is autogenerated.
#ifndef BOOST_TEXT_DATA_FA_AF_HPP
#define BOOST_TEXT_DATA_FA_AF_HPP

#include <boost/text/string_view.hpp>


namespace boost { namespace text { namespace data { namespace fa_AF {

inline string_view standard_collation_tailoring()
{
    return string_view(
u8R"(  
[normalization on]
[reorder Arab]
&َ<<ِ<<ُ<<ً<<ٍ<<ٌ
&[before 1]ا<آ
&ا<<أ<<ٲ<<ٱ<<إ<<ٳ<ء
&ت<ټ<<ٹ
&ج<ځ<<حٔ
&چ<څ
&د<ډ<<ڈ
&ر<ړ<<ڑ
&ژ<ږ
&ک<<*ڪك
&ګ<<گ
&ڼ<<ڻ
&و<<ؤ<<ۇ<<ۉ
&ه<<<ۀ<<<هٔ<<*ەہھةۃ
&ی<<*ىےيېۍ<<یٔ<<<ىٔ<<<ئ
&\u00A0<<\u200C<<\u200D
  )");
}


}}}}

#endif
