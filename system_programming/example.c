static pthread_key_t key; /* 0xff  */
static pthread_once_t key_once = PTHREAD_ONCE_INIT;


static void make_key()
{
    (void) pthread_key_create(&key, NULL);
}


func()
{
    void *ptr; /* thread 1: NULL * thread 2 : NULL */


    (void) pthread_once(&key_once, make_key);
    if ((ptr = pthread_getspecific(key)) == NULL) {
        ptr = malloc(OBJECT_SIZE); /* THREAD 1: 88 */
        ...                        /* THREAD 2: 89 */
        (void) pthread_setspecific(key, ptr); /* thread 1: key(0xff)->data = 88 */
    }
    ...
}