#ifndef UTILS_STRINGUTILS_H
#define UTILS_STRINGUTILS_H
#include <cstdint>
namespace Utils::StringUtils
{
template <typename T, uint8_t N>
auto __int_to_array_offset_impl(T value, char (&chr)[N], uint8_t offset, bool is_negative)
  -> uint8_t
{
  if (offset >= (N - 1))
  {
    return 0;
  }

  uint8_t i = offset;

  if (value == 0)
  {
    if (i < (N - 1))
    {
      chr[i++] = '0';
    }
    chr[i] = '\0';
    return (i - offset);
  }

  // 2. Extract digits backward starting from the offset index
  while (value > 0 && i < (N - 1))
  {
    chr[i++]  = static_cast<char>((value % 10) + '0');
    value    /= 10;
  }

  // 3. Append minus sign for negative numbers
  if (is_negative && i < (N - 1))
  {
    chr[i++] = '-';
  }

  chr[i] = '\0'; // Always null-terminate safely

  // 4. Reverse only the newly added characters in-place
  uint8_t written_len = i - offset;
  for (uint8_t j = 0; j < written_len / 2; ++j)
  {
    char temp                         = chr[offset + j];
    chr[offset + j]                   = chr[offset + written_len - 1 - j];
    chr[offset + written_len - 1 - j] = temp;
  }

  return written_len;
}

// --- Unsigned Overloads ---
template <uint8_t N>
auto ToCharArray(const uint32_t value, char (&chr)[N], uint8_t offset = 0U) -> uint8_t
{
  return __int_to_array_offset_impl(value, chr, offset, false);
}

template <uint8_t N>
auto ToCharArray(const uint16_t value, char (&chr)[N], uint8_t offset = 0U) -> uint8_t
{
  return ToCharArray(static_cast<uint32_t>(value), chr, offset);
}

template <uint8_t N>
auto ToCharArray(const uint8_t value, char (&chr)[N], uint8_t offset = 0U) -> uint8_t
{
  return ToCharArray(static_cast<uint32_t>(value), chr, offset);
}

// --- Signed Overloads ---
template <uint8_t N>
auto ToCharArray(const int32_t value, char (&chr)[N], uint8_t offset = 0U) -> uint8_t
{
  uint32_t uval = static_cast<uint32_t>(value);
  bool is_neg   = false;
  if (value < 0)
  {
    is_neg = true;
    uval   = static_cast<uint32_t>(-value);
  }
  return __int_to_array_offset_impl(uval, chr, offset, is_neg);
}

template <uint8_t N>
auto ToCharArray(const int16_t value, char (&chr)[N], uint8_t offset = 0U) -> uint8_t
{
  return ToCharArray(static_cast<int32_t>(value), chr, offset);
}

template <uint8_t N>
auto ToCharArray(const int8_t value, char (&chr)[N], uint8_t offset = 0U) -> uint8_t
{
  return ToCharArray(static_cast<int32_t>(value), chr, offset);
}

} // namespace Utils::StringUtils
#endif /* UTILS_STRINGUTILS_H */
