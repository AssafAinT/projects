#include <stdio.h> /* printf*/
#include <stdlib.h> /*malloc*/
#define UNUSED(param)  (void)param
struct VtblPublicTransport
{
    void(* dtor_ptr)();
    void(* display)();

};
struct PublicTransport
{
    void *VPTR;
    int m_license_plate;

};

// fixme: add namespace name mangling
static int s_count = 0;

void DtorPublicTransport(struct PublicTransport *this)
{
    --s_count;
    printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
}

void PTdisplay(struct PublicTransport *this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

int get_ID(struct PublicTransport *this)
{
    return this->m_license_plate;
}
// fixme: name mangling
static void print_count(void)
{
    printf("s_count: %d\n",s_count);
}

struct VtblPublicTransport vtbl_ptransport = {DtorPublicTransport, PTdisplay};

void PublicTransportCctor(struct PublicTransport *this, const struct PublicTransport *other)
{
    this->VPTR = &vtbl_ptransport;
    this->m_license_plate = ++s_count;
    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}
void CtorPublicTransport(struct PublicTransport *this) 
{
    this->VPTR = &vtbl_ptransport;
    this->m_license_plate = ++s_count;
    printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
}

struct VtblMinibus
{
    struct VtblPublicTransport vtbl_ptransport;
    void (* wash)();
};

struct Minibus
{
    struct PublicTransport public_transport;
    int m_numSeats;
};
void DtorMiniBus(struct Minibus *this)
{
    (void)this;
    printf("Minibus::Dtor()\n");
    DtorPublicTransport(&this->public_transport); 
}

void MBdisplay(struct Minibus *this)
{
    printf("Minibus::display() ID:%d",get_ID((&this->public_transport)));
    printf(" num seats:%d\n",this->m_numSeats);
}
void Wash(struct Minibus *this, int minutes)
{
   printf("Minibus::wash(%d) ID:%d\n", minutes, get_ID((&this->public_transport)));
}
struct VtblMinibus vtbl_minibus = {{DtorMiniBus, MBdisplay},Wash};
void CtorMiniBus(struct Minibus *this) 
{
    this->m_numSeats = 20;
    CtorPublicTransport(&this->public_transport);
    this->public_transport.VPTR = &vtbl_minibus;
    printf("Minibus::Ctor()\n");
}

void CCtorMiniBus(struct Minibus *this, const struct Minibus *other) 
{
    PublicTransportCctor(&(this->public_transport), &(other->public_transport));
    this->m_numSeats = other->m_numSeats;
    this->public_transport.VPTR = &vtbl_minibus;
    printf("Minibus::CCtor()\n");
}

struct VtblTaxi
{
    struct VtblPublicTransport vtbl_ptransport;
};
struct Taxi
{
    struct PublicTransport public_transport;
};


void DtorTaxi(struct Taxi *this)
{
    (void)this;
    printf("Taxi::Dtor()\n");
    DtorPublicTransport(&this->public_transport); 
}
void DeleteTaxiArray(struct Taxi *arr4, size_t element_amount)
{
    struct Taxi *runner = &arr4[(element_amount -1)];
    for (size_t i = 0; i < element_amount; ++i, --runner)
    {
        DtorTaxi(runner);
    }
    free(arr4);
}

void Taxidisplay(struct Taxi *this)
{
    printf("Taxi::display() ID:%d\n",get_ID((&this->public_transport)));
}
struct VtblTaxi vtbl_taxi = {{DtorTaxi, Taxidisplay}};
void CtorTaxi(struct Taxi *this) 
{
    CtorPublicTransport(&this->public_transport);
    this->public_transport.VPTR = &vtbl_taxi;
    printf("Taxi::Ctor()\n");
}

void CCtorTaxi(struct Taxi *this, const struct Taxi *other) 
{
    PublicTransportCctor(&(this->public_transport), &(other->public_transport));
    this->public_transport.VPTR = &vtbl_taxi;
    printf("Taxi::CCtor()\n");
}

#define TEMPLATE_MAX(T)\
T max_func(T a,T b)\
{\   
    return a > b ? a : b;\   
}

TEMPLATE_MAX(int)

struct SpecialTaxi
{
    void *VPTR;
    struct Taxi taxi;
}SpecialTaxi;

void SpecialTaxiCtor(struct SpecialTaxi *this);
/*virtual*/ void SpecialTaxiDtor(struct SpecialTaxi *this);
void SpecialTaxiCopy(struct SpecialTaxi *this, struct SpecialTaxi *other);
void SpecialTaxiDisplay(struct SpecialTaxi *this);
struct SpecialTaxi *SpecialTaxiNew();

struct SpecialTaxi_VTable
{
    struct VtblTaxi taxi_vtable;
};

struct SpecialTaxi_VTable g_st_vtable = {{{SpecialTaxiDisplay, SpecialTaxiDtor}}}; 

void taxi_display(struct Taxi s)
{
    ((struct VtblPublicTransport *)(s.public_transport.VPTR))->display(&s);

}

void SpecialTaxiCtor(struct SpecialTaxi *this)
{
    CtorTaxi(&(this->taxi));
    this->VPTR = &g_st_vtable;
    printf("SpecialTaxi::Ctor()\n");
}

/*virtual*/ void SpecialTaxiDtor(struct SpecialTaxi *this)
{
    printf("SpecialTaxi::Dtor()\n");
    DtorTaxi(&(this->taxi));
}

void SpecialTaxiCopy(struct SpecialTaxi *this, struct SpecialTaxi *other)
{
    CCtorTaxi(&(this->taxi), &(other->taxi));
    this->VPTR = &g_st_vtable;
    printf("SpecialTaxi::CCtor()\n");
}

void SpecialTaxiDisplay(struct SpecialTaxi *this)
{
    printf("SpecialTaxi::display() ID:%d\n",get_ID(&(this->taxi.public_transport)));
}
void Vprint_infoV(struct PublicTransport *a)
{
    ((struct VtblPublicTransport *)(a->VPTR))->display();
}

void print_info_no_args()
{
    print_count();
}

void print_info_MiniBus(struct Minibus *m)
{
    ((struct VtblMinibus *)(m->public_transport.VPTR))->wash(m, 3);
}

struct PublicTransport print_info(int i)
{
    struct Minibus ret;
    CtorMiniBus(&ret);
    printf("print_info(int i)\n");
    MBdisplay(&ret);
    
    /* slicing*/ 
    struct PublicTransport sliced;
    PublicTransportCctor(&sliced, &ret.public_transport);

    DtorMiniBus(&ret);
    UNUSED(i);
    return (sliced);
}


struct Minibus *new_minibus(void)
{
    struct Minibus *ret = malloc(sizeof(struct Minibus));
    CtorMiniBus(ret);
    return ret;

}
void MinibusDelete(struct Minibus *this)
{
    ((struct VtblPublicTransport *)(this->public_transport.VPTR))->dtor_ptr(this);
    free(this);
}

struct Taxi *new_taxi(size_t num_of_elements)
{
    struct Taxi *ret = (struct Taxi *)malloc(sizeof(struct Taxi) * num_of_elements);
    if(NULL == ret)
    {
        return NULL;
    }

    struct Taxi *runner = ret;
    for (size_t i = 0; i < num_of_elements; ++i, ++runner)
    {
        CtorTaxi(runner);
    }

    return ret;
}

void TaxiDelete(struct Taxi *this)
{
    ((struct VtblPublicTransport *)(this->public_transport.VPTR))->dtor_ptr(this);
    free(this);

}
struct SpecialTaxi *SpecialTaxiNew()
{
    struct SpecialTaxi *new = malloc(sizeof(struct SpecialTaxi));
    SpecialTaxiCtor(new);

    return (new);
}

struct PublicTransport *new_public_transport(void)
{
    struct PublicTransport *ret = malloc(sizeof(struct PublicTransport));
    
    return ret;

}

struct PublicConvoy
{
    struct PublicTransport public_transport;

    struct PublicTransport *m_pt1;
    struct PublicTransport *m_pt2;
    struct Minibus m_m;
    struct Taxi m_t;
};


/*virtual*/ void PublicConvoyDtor(struct PublicConvoy *this)
{
    ((struct VtblPublicTransport *)(this->m_pt1->VPTR))->dtor_ptr(this->m_pt1);
    ((struct VtblPublicTransport *)(this->m_pt2->VPTR))->dtor_ptr(this->m_pt2);
    DtorTaxi(&(this->m_t));
    DtorMiniBus(&(this->m_m));
    DtorPublicTransport(&(this->public_transport));
}

void PublicConvoyDisplay(struct PublicConvoy *this)
{
    ((struct VtblPublicTransport *)(this->m_pt1->VPTR))->display(this->m_pt1);
    ((struct VtblPublicTransport *)(this->m_pt2->VPTR))->display(this->m_pt2);

    MBdisplay(&(this->m_m));
    Taxidisplay(&(this->m_t));
}

void PublicConvoyDelete(struct PublicConvoy *this)
{
    PublicConvoyDtor(this);
    free(this);
}

struct PublicConvoy_VTable
{
   struct VtblPublicTransport vtbl_ptransport;
};

struct PublicConvoy_VTable g_pc_vtable = {{PublicConvoyDisplay, PublicConvoyDtor}}; 

void PublicConvoyCtor(struct PublicConvoy *this)
{
    CtorPublicTransport(&(this->public_transport));
    this->public_transport.VPTR = &g_pc_vtable;
    this->m_pt1 = (struct PublicTransport *)new_minibus();
    this->m_pt2 = (struct PublicTransport *)new_taxi(1);
    CtorMiniBus(&(this->m_m));
    CtorTaxi(&(this->m_t));
}

void PublicConvoyCCtor(struct PublicConvoy *this, struct PublicConvoy *other)
{
    PublicTransportCctor(&(this->public_transport), &(other->public_transport));
    this->public_transport.VPTR = &g_pc_vtable;

    this->m_pt1 = (struct PublicTransport *)malloc(sizeof(struct Minibus));
    this->m_pt2 = (struct PublicTransport *)malloc(sizeof(struct Taxi));
    CCtorMiniBus((struct Minibus *)(this->m_pt1), (struct Minibus *)(other->m_pt1));
    CCtorTaxi((struct Taxi *)(this->m_pt2), (struct Taxi *)(other->m_pt2));

    CCtorMiniBus(&(this->m_m), &(other->m_m));
    CCtorTaxi(&(this->m_t), &(other->m_t));
}
struct PublicConvoy *PublicConvoyNew()
{
    struct PublicConvoy *new = (struct PublicConvoy *)
                               malloc(sizeof(struct PublicConvoy));
    PublicConvoyCtor(new);

    return (new);
}

struct PublicConvoy *PublicConvoyNewCopy(struct PublicConvoy *other)
{
    struct PublicConvoy *new = (struct PublicConvoy *)malloc(sizeof(struct PublicConvoy));
    PublicConvoyCCtor(new, other);

    return (new);
}
int main(void)
{
    struct Minibus m;
    CtorMiniBus(&m);

    print_info_MiniBus(&m);
    struct PublicTransport ret_func = print_info(3);
    ((struct VtblPublicTransport *)ret_func.VPTR)->display(&ret_func);
    DtorPublicTransport(&ret_func);
     
    struct PublicTransport *array[] = 
    {
       (struct PublicTransport *)new_minibus(),
       (struct PublicTransport *)new_taxi(1),
       (struct PublicTransport *)new_minibus()
    };

    for (int i = 0; i < 3; ++i) 
    {
        ((struct VtblPublicTransport*)(array[i]->VPTR))->display(array[i]);
    }

    for (int i = 0; i < 3; ++i) 
    {
        ((struct VtblPublicTransport*)(array[i]->VPTR))->dtor_ptr(array[i]);
        free(array[i]);
    }

    struct Minibus m_arr2;
    CtorMiniBus(&m_arr2);
    struct PublicTransport public_minibus;
    PublicTransportCctor(&public_minibus, &m_arr2.public_transport);
    ((struct VtblPublicTransport *)m_arr2.public_transport.VPTR)->dtor_ptr(&m_arr2);

    struct Taxi m_taxi;
    CtorTaxi(&m_taxi);
    struct PublicTransport public_taxi;
    PublicTransportCctor(&public_taxi, &m_taxi.public_transport);
    ((struct VtblPublicTransport *)m_taxi.public_transport.VPTR)->dtor_ptr(&m_taxi);

    struct PublicTransport public_trans;
    CtorPublicTransport(&public_trans);

    struct PublicTransport arr2[] = 
    {
       public_minibus,
       public_taxi,
       public_trans
    };


    for (int i = 0; i < 3; ++i)
    {
        PTdisplay(&arr2[i]); /*static binding*/
        //((struct VtblPublicTransport*)(arr2[i].VPTR))->display(&arr2[i]);
    }
    Vprint_infoV(&arr2[0]);
    print_count();


    struct Minibus m2;
    CtorMiniBus(&m2);
    print_count();

    struct Minibus arr3[4];
    for (int i = 0; i < 4; ++i)
    {
        CtorMiniBus(&arr3[i]); 
    }

    struct Taxi *arr4 = new_taxi(4);
    DeleteTaxiArray(arr4, 4);

    printf("%d\n",max_func(1, 2));
    printf("%d\n",max_func(1, 2));


    struct SpecialTaxi st;
    SpecialTaxiCtor(&st);

    struct Taxi sliced_taxi;
    struct PublicTransport sliced_transport;
    
    CCtorTaxi(&sliced_taxi, &(st.taxi));
    taxi_display(sliced_taxi);
    DtorTaxi(&sliced_taxi); 


    struct PublicConvoy *ts1 = PublicConvoyNew();
    struct PublicConvoy *ts2 = PublicConvoyNewCopy(ts1);

    PublicConvoyDisplay(ts1);
    PublicConvoyDisplay(ts2);

    PublicConvoyDelete(ts1);

    PublicConvoyDisplay(ts2);

    PublicConvoyDelete(ts2);


    /* stack-allocated dtors */

    SpecialTaxiDtor(&st);

    for (int i = 3 ; i >= 0 ; --i)
    {
        DtorMiniBus(&arr3[i]);
    }

    DtorMiniBus(&m2);

    for (int i = 2 ; i >= 0 ; --i)
    {
         ((struct VtblPublicTransport*)(arr2[i].VPTR))->dtor_ptr(&arr2[i]);
    }
    DtorMiniBus(&m);

    UNUSED(sliced_transport);
    return (0);
}