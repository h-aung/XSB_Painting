CC = icc
CXX= icpc
#CC = CC

CFLAGS = -O2 
CXXFLAGS = -O2 -std=c++11
#CXXFLAGS = -O0 -g
#CXXFLAGS += -DMPI_PARALLEL
#CXXFLAGS += -DOUTPUT_NFW_DENSITY
#CXXFLAGS += -DLONGIDS
#CXXFLAGS += -DEXCLUDE_SUBHALOS
CXXFLAGS += -DMASS_SELECTION=1e12
#CXXFLAGS += -DROCKSTAR_CONCENTRATION
CFLAGS += -I/usr/local/include -I/home/fas/nagai/etl28/Xrays/cfitsio
CXXFLAGS += -I/usr/local/include

CLIBS = -lgsl -lgslcblas -lm -L/home/fas/nagai/etl28/Xrays/cfitsio -lcfitsio

APEC_SRCS = Apec.c atomdb_make_spectrum.c calc_continuum.c calc_lines.c messages.c readapec.c read_continuum_data.c read_fits_spectrum.c read_line_data.c read_parameters.c gaussianLine.c

APEC_OBJS = $(patsubst %.c,Apec/%.o,$(APEC_SRCS))

Apec/%.o: Apec/%.c Apec/%.h
	$(CC) $(CFLAGS) $(FCOCO) $(FLINE) -I. -I./Apec -c $< -o $@

sbprof: main.cpp gas_model.o read_halo xray.o ConfigParser.o $(APEC_OBJS)
	$(CXX) $(CXXFLAGS) -o sbprof main.cpp gas_model.o xray.o read_halo_rs.o read_lightcone.o ConfigParser.o $(APEC_OBJS) $(CLIBS) 

xray.o: xray.c xray.h
	$(CC) $(CFLAGS) -c xray.c

gas_model.o: gas_model.cpp gas_model.h
	$(CXX) $(CXXFLAGS) -c gas_model.cpp

read_halo: io/read_lightcone.cpp io/read_halo_rs.cpp  io/read_halo.h
	$(CXX) $(CXXFLAGS) -c io/read_lightcone.cpp io/read_halo_rs.cpp

ConfigParser.o: ConfigParser/ConfigParser.c ConfigParser/ConfigParser.h
	$(CC) -c ConfigParser/ConfigParser.c

clean:
	/bin/rm -f *.o Apec/*.o sbprof
