#include <boost/text/normalize.hpp>
#include <boost/text/normalize_string.hpp>
#include <boost/text/string_view.hpp>

#include <boost/text/detail/icu/normalize.hpp>

#include <unicode/normalizer2.h>

#include <benchmark/benchmark.h>

#include <fstream>
#include <iostream>


std::string file_contents;
boost::text::string file_contents_text_string;
std::vector<uint32_t> file_cps;

U_NAMESPACE_QUALIFIER UnicodeString file_contents_ustr;

UErrorCode ec = U_ZERO_ERROR;
U_NAMESPACE_QUALIFIER Normalizer2 const * const to_nfd =
    U_NAMESPACE_QUALIFIER Normalizer2::getNFDInstance(ec);
U_NAMESPACE_QUALIFIER Normalizer2 const * const to_nfc =
    U_NAMESPACE_QUALIFIER Normalizer2::getNFCInstance(ec);
U_NAMESPACE_QUALIFIER Normalizer2 const * const to_nfkd =
    U_NAMESPACE_QUALIFIER Normalizer2::getNFKDInstance(ec);
U_NAMESPACE_QUALIFIER Normalizer2 const * const to_nfkc =
    U_NAMESPACE_QUALIFIER Normalizer2::getNFKCInstance(ec);
U_NAMESPACE_QUALIFIER Normalizer2 const * const to_fcc =
    U_NAMESPACE_QUALIFIER Normalizer2::getInstance(
        nullptr, "nfc", UNORM2_COMPOSE_CONTIGUOUS, ec);


void BM_icu_utf8_fcc(benchmark::State & state)
{
    while (state.KeepRunning()) {
        std::string result;
        U_NAMESPACE_QUALIFIER StringByteSink<std::string> sink(&result);
        to_fcc->normalizeUTF8(
            0,
            U_NAMESPACE_QUALIFIER StringPiece(file_contents),
            sink,
            nullptr,
            ec);
        benchmark::ClobberMemory();
    }
}

void BM_text_utf8_fcc(benchmark::State & state)
{
    while (state.KeepRunning()) {
        std::vector<char> normalized;
        auto r = boost::text::make_to_utf32_range(
            boost::text::string_view(file_contents));
        benchmark::DoNotOptimize(boost::text::normalize_to_fcc(
            r, boost::text::utf_32_to_8_back_inserter(normalized)));
    }
}

void BM_text_utf8_fcc_string_append(benchmark::State & state)
{
    while (state.KeepRunning()) {
        std::string result;
        auto r = boost::text::make_to_utf32_range(
            boost::text::string_view(file_contents));
        normalize_to_fcc_append_utf8(r, result);
        benchmark::ClobberMemory();
    }
}

void BM_text_icu_utf8_fcc_string_append(benchmark::State & state)
{
    while (state.KeepRunning()) {
        std::string result;
        auto sv = boost::text::string_view(file_contents);
        boost::text::detail::icu::utf8_normalize_to_fcc_append(
            sv.begin(), sv.end(), result);
        benchmark::ClobberMemory();
    }
}

void BM_text_utf8_fcc_string(benchmark::State & state)
{
    while (state.KeepRunning()) {
        state.PauseTiming();
        boost::text::string s(file_contents);
        state.ResumeTiming();
        normalize_to_fcc(s);
        benchmark::ClobberMemory();
    }
}

void BM_icu_utf8_nfd(benchmark::State & state)
{
    while (state.KeepRunning()) {
        std::string result;
        U_NAMESPACE_QUALIFIER StringByteSink<std::string> sink(&result);
        to_nfd->normalizeUTF8(
            0,
            U_NAMESPACE_QUALIFIER StringPiece(file_contents),
            sink,
            nullptr,
            ec);
        benchmark::ClobberMemory();
    }
}

void BM_icu_utf16_nfd(benchmark::State & state)
{
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(to_nfd->normalize(file_contents_ustr, ec));
    }
}

void BM_text_utf8_nfd(benchmark::State & state)
{
    while (state.KeepRunning()) {
        std::vector<char> normalized;
        auto r = boost::text::make_to_utf32_range(
            boost::text::string_view(file_contents));
        benchmark::DoNotOptimize(boost::text::normalize_to_nfd(
            r, boost::text::utf_32_to_8_back_inserter(normalized)));
    }
}

void BM_text_utf8_nfd_string(benchmark::State & state)
{
    while (state.KeepRunning()) {
        state.PauseTiming();
        auto str = file_contents_text_string;
        state.ResumeTiming();
        boost::text::normalize_to_nfd(str);
        benchmark::ClobberMemory();
    }
}

void BM_text_utf32_nfd(benchmark::State & state)
{
    while (state.KeepRunning()) {
        std::vector<uint32_t> normalized;
        benchmark::DoNotOptimize(boost::text::normalize_to_nfd(
            file_cps, std::back_inserter(normalized)));
    }
}

void BM_icu_utf8_nfc(benchmark::State & state)
{
    while (state.KeepRunning()) {
        std::string result;
        U_NAMESPACE_QUALIFIER StringByteSink<std::string> sink(&result);
        to_nfc->normalizeUTF8(
            0,
            U_NAMESPACE_QUALIFIER StringPiece(file_contents),
            sink,
            nullptr,
            ec);
        benchmark::ClobberMemory();
    }
}

void BM_icu_utf16_nfc(benchmark::State & state)
{
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(to_nfc->normalize(file_contents_ustr, ec));
    }
}

void BM_text_utf8_nfc(benchmark::State & state)
{
    while (state.KeepRunning()) {
        std::vector<char> normalized;
        auto r = boost::text::make_to_utf32_range(
            boost::text::string_view(file_contents));
        benchmark::DoNotOptimize(boost::text::normalize_to_nfc(
            r, boost::text::utf_32_to_8_back_inserter(normalized)));
    }
}

void BM_text_utf8_nfc_string(benchmark::State & state)
{
    while (state.KeepRunning()) {
        state.PauseTiming();
        auto str = file_contents_text_string;
        state.ResumeTiming();
        boost::text::normalize_to_nfc(str);
        benchmark::ClobberMemory();
    }
}

void BM_text_utf32_nfc(benchmark::State & state)
{
    while (state.KeepRunning()) {
        std::vector<uint32_t> normalized;
        benchmark::DoNotOptimize(boost::text::normalize_to_nfc(
            file_cps, std::back_inserter(normalized)));
    }
}

void BM_icu_utf8_nfkd(benchmark::State & state)
{
    while (state.KeepRunning()) {
        std::string result;
        U_NAMESPACE_QUALIFIER StringByteSink<std::string> sink(&result);
        to_nfkd->normalizeUTF8(
            0,
            U_NAMESPACE_QUALIFIER StringPiece(file_contents),
            sink,
            nullptr,
            ec);
        benchmark::ClobberMemory();
    }
}

void BM_icu_utf16_nfkd(benchmark::State & state)
{
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(to_nfkd->normalize(file_contents_ustr, ec));
    }
}

void BM_text_utf8_nfkd(benchmark::State & state)
{
    while (state.KeepRunning()) {
        std::vector<char> normalized;
        auto r = boost::text::make_to_utf32_range(
            boost::text::string_view(file_contents));
        benchmark::DoNotOptimize(boost::text::normalize_to_nfkd(
            r, boost::text::utf_32_to_8_back_inserter(normalized)));
    }
}

void BM_text_utf8_nfkd_string(benchmark::State & state)
{
    while (state.KeepRunning()) {
        state.PauseTiming();
        auto str = file_contents_text_string;
        state.ResumeTiming();
        boost::text::normalize_to_nfkd(str);
        benchmark::ClobberMemory();
    }
}

void BM_text_utf32_nfkd(benchmark::State & state)
{
    while (state.KeepRunning()) {
        std::vector<uint32_t> normalized;
        benchmark::DoNotOptimize(boost::text::normalize_to_nfkd(
            file_cps, std::back_inserter(normalized)));
    }
}

void BM_icu_utf8_nfkc(benchmark::State & state)
{
    while (state.KeepRunning()) {
        std::string result;
        U_NAMESPACE_QUALIFIER StringByteSink<std::string> sink(&result);
        to_nfkc->normalizeUTF8(
            0,
            U_NAMESPACE_QUALIFIER StringPiece(file_contents),
            sink,
            nullptr,
            ec);
        benchmark::ClobberMemory();
    }
}

void BM_icu_utf16_nfkc(benchmark::State & state)
{
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(to_nfkc->normalize(file_contents_ustr, ec));
    }
}

void BM_text_utf8_nfkc(benchmark::State & state)
{
    while (state.KeepRunning()) {
        std::vector<char> normalized;
        auto r = boost::text::make_to_utf32_range(
            boost::text::string_view(file_contents));
        benchmark::DoNotOptimize(boost::text::normalize_to_nfkc(
            r, boost::text::utf_32_to_8_back_inserter(normalized)));
    }
}

void BM_text_utf8_nfkc_string(benchmark::State & state)
{
    while (state.KeepRunning()) {
        state.PauseTiming();
        auto str = file_contents_text_string;
        state.ResumeTiming();
        boost::text::normalize_to_nfkc(str);
        benchmark::ClobberMemory();
    }
}

void BM_text_utf32_nfkc(benchmark::State & state)
{
    while (state.KeepRunning()) {
        std::vector<uint32_t> normalized;
        benchmark::DoNotOptimize(boost::text::normalize_to_nfkc(
            file_cps, std::back_inserter(normalized)));
    }
}

BENCHMARK(BM_icu_utf8_fcc);
BENCHMARK(BM_text_utf8_fcc);
BENCHMARK(BM_text_utf8_fcc_string_append);
BENCHMARK(BM_text_icu_utf8_fcc_string_append);
BENCHMARK(BM_text_utf8_fcc_string);
BENCHMARK(BM_icu_utf8_nfd);
BENCHMARK(BM_icu_utf16_nfd);
BENCHMARK(BM_text_utf8_nfd);
BENCHMARK(BM_text_utf8_nfd_string);
BENCHMARK(BM_text_utf32_nfd);
BENCHMARK(BM_icu_utf8_nfc);
BENCHMARK(BM_icu_utf16_nfc);
BENCHMARK(BM_text_utf8_nfc);
BENCHMARK(BM_text_utf8_nfc_string);
BENCHMARK(BM_text_utf32_nfc);
BENCHMARK(BM_icu_utf8_nfkd);
BENCHMARK(BM_icu_utf16_nfkd);
BENCHMARK(BM_text_utf8_nfkd);
BENCHMARK(BM_text_utf8_nfkd_string);
BENCHMARK(BM_text_utf32_nfkd);
BENCHMARK(BM_icu_utf8_nfkc);
BENCHMARK(BM_icu_utf16_nfkc);
BENCHMARK(BM_text_utf8_nfkc);
BENCHMARK(BM_text_utf8_nfkc_string);
BENCHMARK(BM_text_utf32_nfkc);

int main(int argc, char ** argv)
{
    if (argc < 2) {
        std::cerr << "Error: No input file provided." << std::endl;
        return 1;
    }

    // Last arg must be the name of the file to parse.
    char const * filename = argv[argc - 1];
    std::ifstream ifs(filename, std::ios_base::binary);

    if (!ifs) {
        std::cerr << "Error: Could not open input file: " << filename
                  << std::endl;
        return 1;
    }

    getline(ifs, file_contents, '\0');
    file_contents_text_string = file_contents;
    auto const file_cp_range = boost::text::make_to_utf32_range(
        boost::text::string_view(file_contents));
    file_cps.assign(file_cp_range.begin(), file_cp_range.end());
    file_contents_ustr = U_NAMESPACE_QUALIFIER UnicodeString::fromUTF8(
        U_NAMESPACE_QUALIFIER StringPiece(file_contents));

    int argc_ = argc - 1; // Don't give filename arg to Benchmark.

#if 0
    if (1 < argc_ && argv[argc_ - 1] == std::string("-v")) {
        verbose = true;
        --argc_;
    }
#endif

    ::benchmark::Initialize(&argc_, argv);
    ::benchmark::RunSpecifiedBenchmarks();
}

// BENCHMARK_MAIN()
