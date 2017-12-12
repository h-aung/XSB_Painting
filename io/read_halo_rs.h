#ifndef _READ_HALO_RS_
#define _READ_HALO_RS_

typedef struct {
    long id, pid;
    float x, y, z; //pixel unitis in ray-tracing simulation
    float redshift, Xoff;
    float rs, rvir, Mvir; //scale radius, virial radius in comoving kpc/h, virial mass in Msun/h
    float M200c, M500c; // in Msun/h
} rs_halo_struct ;

typedef struct {
    int num_halos;
    rs_halo_struct *list;
} rs_halo_list;

rs_halo_list *load_halo_rs ( const char *filename );
void destroy_rs_halo_list (rs_halo_list *halos);

#endif
