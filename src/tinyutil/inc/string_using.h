/*
 * string_using.h
 *
 *  Created on: Jun 11, 2019
 *      Author: wangwei69
 */

#ifndef SRC_INC_STRING_USING_H_
#define SRC_INC_STRING_USING_H_

#include <string>



void string_com_use();
void string_match_way();
bool verify_unicode(const char *str);
int string_unicode_utf8(const char *src,std::string &des);
int is_chinese_english();
size_t split_string(const std::string& src,
                    const std::string& delimiter,
                    std::vector<std::string> &fields);

int get_first_digit_pos(const char *str);
bool is_gb18030_four_bytes(const char* src, size_t len);
bool is_gb18030_double_bytes(const char* src, size_t len);
void parse_address_norm(std::string &address_norm);


#endif /* SRC_INC_STRING_USING_H_ */
