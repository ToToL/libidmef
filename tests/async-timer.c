#include "config.h"

#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "libidmef.h"

#include "glthread/lock.h"


struct asyncobj {
        LIBIDMEF_ASYNC_OBJECT;
        int myval;
};


static int async_done = 0;
static int timer_count = 0;
static gl_lock_t lock = gl_lock_initializer;


static void timer_cb(void *data)
{
        gl_lock_lock(lock);
        timer_count++;
        libidmef_timer_reset(data);
        gl_lock_unlock(lock);
}


static void async_func(void *obj, void *data)
{
        struct asyncobj *ptr = obj;

        gl_lock_lock(lock);
        async_done = 1;
        assert(ptr->myval == 10);
        gl_lock_unlock(lock);
}


int main(void)
{
        libidmef_timer_t timer;
        struct asyncobj myobj;

        assert(libidmef_init(NULL, NULL) == 0);
        assert(libidmef_async_init() == 0);
        libidmef_async_set_flags(LIBIDMEF_ASYNC_FLAGS_TIMER);

        libidmef_timer_set_expire(&timer, 1);
        libidmef_timer_set_data(&timer, &timer);
        libidmef_timer_set_callback(&timer, timer_cb);
        libidmef_timer_init(&timer);

        sleep(3);

        gl_lock_lock(lock);
        assert(timer_count >= 2);
        gl_lock_unlock(lock);

        myobj.myval = 10;
        libidmef_async_set_callback((libidmef_async_object_t *) &myobj, async_func);
        libidmef_async_add((libidmef_async_object_t *) &myobj);

        libidmef_async_exit();
        assert(async_done);

        libidmef_deinit();
        exit(0);
}
