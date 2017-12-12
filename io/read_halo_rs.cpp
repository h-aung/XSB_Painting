#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "read_halo.h"

using namespace std;

halo_list *load_halo_rs ( const char *filename ) {
    int i;
    int halo_count = 0;
    string line;

    long id, pid;
    float r, x, y, z, M200c, M500c, Xoff, rs, scale;

    halo_list *halos;

    ifstream file(filename);

    if (file.is_open()) {
        while (getline(file, line))
            ++halo_count;

        cout << "Number of halos: " << halo_count << endl;
        halos = (halo_list *)malloc(sizeof(halo_list));
        halos->num_halos = halo_count;

        halos->list = (halo_struct *) malloc (halo_count*sizeof(halo_struct));

        file.clear();
        file.seekg(0, ios::beg);

        for (i = 0; i < halos->num_halos; i++) {
            file >> id >> scale >> pid >> r >> x >> y >> z >> M200c >> M500c >> Xoff;
            halos->list[i].id = id;
            halos->list[i].pid = pid;
            halos->list[i].x = x;
            halos->list[i].y = y;
            halos->list[i].z = z;
	    halos->list[i].redshift = (1/scale)-1;
            halos->list[i].rvir = r;
            halos->list[i].rs = rs;
            halos->list[i].Mvir = M200c;
	    halos->list[i].M500c = M500c;
            halos->list[i].M200c = M200c;
	    halos->list[i].Xoff = Xoff;
        }

        file.close();

    } else {
        cout << "Unable to open file" << endl;
        exit(1);
    }
    return halos;
}