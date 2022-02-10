/*
 * 3_hex_to_dec.cpp
 *
 *  Created on: 2016��6��14��
 *      Author: wangwei69
 */


/*
 * 16���Ƶ�����(�ַ���)ת����10���Ƶ�����
 * ���磺4c ->  76
 */

#include<string>
#include<iostream>

bool  hex_2_dec(std::string hex,int &res){

    const std::string table = "0123456789ABCDEF";
    std::string::size_type len = hex.size();
    res = 0;
    unsigned int exp = 1;
    for(auto i = len;i > 0;i--){
        char ch = toupper(hex[i-1]);
        //std::cout << "ch:"  <<ch <<std::endl;
        std::string::size_type ind = table.find(ch);
        if(ind!=std::string::npos){//������ַ��ڴʱ��У��Ϸ��ַ�
            res += (ind * exp);
            exp *= 16;
        }else{
            std::cout <<"Has illegal character" <<std::endl;
            return false;
        }
    }

    return true;

}


