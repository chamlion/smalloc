#include "smalloc.h"
#include<iostream>
#include<mutex>
//#include <linux/irq.h>
// extern unsigned irq_disable();
// extern void irq_restore(unsigned);
namespace smalloc
{
    SMalloc::SMalloc(size_t size)
        : size_{size}
    {
        heap_ = malloc(size);
        if(heap_ == nullptr){
            std::cout<<"SMalloc malloc error"<<std::endl;
        }

        tlsf_ = tlsf_create_with_pool(heap_, size);
    }
    SMalloc::~SMalloc()
    {
        tlsf_destroy(tlsf_);
        free(heap_);
    }

    void *SMalloc::Malloc(size_t size)
    {
        return tlsf_malloc(tlsf_, size);
    }

    void SMalloc::Free(void *ptr)
    {
        return tlsf_free(tlsf_, ptr);
    }
    thread_local static SMalloc sMalloc(1024 * 1024 * 128);
    void *smalloc(size_t size)
    {
     //   unsigned old_state = irq_disable();
        auto* ptr =  sMalloc.Malloc(size);
    //    irq_restore(old_state);
        return ptr;
    }

    void sfree(void *ptr)
    {
    //    unsigned old_state = irq_disable();
        sMalloc.Free(ptr);
    //    irq_restore(old_state);
    }


    static SMalloc sMalloc_s(1024 * 1024 * 512);
    std::mutex gMutex;
    void *smalloc_s(size_t size)
    {
     //   unsigned old_state = irq_disable();
        std::lock_guard<std::mutex> locker{gMutex};
        auto* ptr =  sMalloc_s.Malloc(size);
    //    irq_restore(old_state);
        return ptr;
    }

    void sfree_s(void *ptr)
    {
    std::lock_guard<std::mutex> locker{gMutex};
    //    unsigned old_state = irq_disable();
        sMalloc_s.Free(ptr);
    //    irq_restore(old_state);
    }
}