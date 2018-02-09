# XSB_Painting

Paint X-ray surface brightness profile and projected 2D temperature profile for a given DM halo. Takes input from halo catalog by Masato Shirasaki (NAOJ). Gas properties is determined by the ICM model by Flender et al (2017), which is based on Shaw et al (2010). Original code by S. Bhattacharya, modified by S. Flender, K. Osato, and E. Lau.

##### Usage

`make` to compile

`./sbprof example.cfg` to run. Check example.cfg for parameters

##### Concentration

When `file_format = simple`, concentration-mass relation is assumed from Dutton, Maccio 2014, and c200c is then converted to c500c by assuming NFW profile.