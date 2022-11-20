#include "shared_ptr.hpp"

namespace SharedPtrUtils
{
    void Deatach(ilrd::SharedPtr<T>* ptr)
    {
        --*(ptr->GetCounter());
        if ( 0 == *ptr->GetCounter())
        {
            delete ptr;
        }

    }
}
