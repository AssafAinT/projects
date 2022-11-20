#ifndef __ILRD_RD127_128_SHAPE_HPP__
#define __ILRD_RD127_128_SHAPE_HPP__

#include <list>
#include <cstddef> //size_t

#if _cplusplus<201104
#define noexcept throw()
#endif //#if _cplusplus<201104

namespace ilrd
{

    class IShape
    {
        public:
            virtual ~IShape() noexcept {}
            virtual void Draw() const = 0;  
            virtual IShape& Move() = 0;

            static void DrawList(const std::list<IShape*> shapeList);
    };

    class Shape : public IShape
    {
        public:
            Shape(): m_offset(0){}
            virtual ~Shape() noexcept {}
            virtual IShape& Move();

        protected:
            size_t GetOffset() const;

        private:
            size_t m_offset;
    };

    class Line : public Shape
    {
        public:
            virtual void Draw() const;
    };

    class Circle : public Shape
    {
        public:
            virtual void Draw() const;
    };

    class Rectangle : public Shape
    {
        public:
            virtual void Draw() const;
    };

    class Square : public Shape
    {
        public:
            virtual void Draw() const;
    };

}

#endif //__ILRD_RD127_128_SHAPE_HPP__
