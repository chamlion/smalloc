#ifndef S_MALLOC_H_
#define S_MALLOC_H
#include "tlsf.h"
namespace smalloc
{
    class SMalloc
    {
    public:
        explicit SMalloc(size_t size);
        ~SMalloc();
        void *Malloc(size_t size);
        void Free(void *ptr);

    private:
        size_t size_;
        void *heap_;
        tlsf_t tlsf_;
    };

    void *smalloc(size_t size);

    void sfree(void *ptr);
        void *smalloc_s(size_t size);

    void sfree_s(void *ptr);

    // class SMalloc
    // {
    // public:
    //     SMallco(size_t size) = default;
    //     void *malloc(size_t size);
    //     void free(void *ptr);

    // private:
    //     thread_local CtlBlock ctlBlock_;
    // }
}

#endif