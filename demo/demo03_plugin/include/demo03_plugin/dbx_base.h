#ifndef DBX_BASE_H
#define DBX_BASE_H

namespace dbx_base_ns
{
    // 必须保证基类中包含无参构造 
    class Dbx_Base
    {
        protected:
            Dbx_Base(){}
        public:
            // 计算周长的函数
            virtual double getlength() = 0;
            // 初始化边长的函数
            virtual void init(double side_length) = 0;
    };
} 


#endif