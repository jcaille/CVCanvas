CVCanvas
========

This is the repository for the CVCanvas Project @ Telecom ParisTech
The objective is to be able to remove lightning artifacts (such as reflection, specularity and lambertian reflets) on paintings, using multiple pictures of the same painting, from different angles. We used the method described in this [article](http://www.dtic.upf.edu/~gharo/Download/paintings_siims_no_compression.pdf)

## Build Instructions
The repo does not contain any project or build settings (Difficult to share across plateforms). We however have included almost everything neeed to run the project :

* `CVCanvas`folder contains the source code.
* `Images` folder the images referenced in the source code.

To build, you might have to link against OpenCV (We used OpenCV 2.4.9), and set the working directory or search path for additional files to the `Images` folder.

## Code Architecture

The method used calls for two steps : Fitting and Merging. We have implemented several strategies for each operation, allowing to easily compare results.

* `ImageLoader.h/m` contains the function loading the images set from disk
* `ImageFitter.h/m` dispatches between the different fitting strategies
	* `NONE` : Do not fit images
	* `USER` : Ask the User to fit the images by clicking on the painting's corner
	* `SIFT` : Automatticaly fit the images using SIFT descriptors and RANSAC algorithm.
* `ImageMerger.h/m`dispatches between the different merging strategies
	* `AVERAGE`: Average all images
	* `MINIMUM`: For each pixel, each channel is set to the minimum value of this channel in all image
	* `MEDIAN`: For each pixel, each channel is set to the median value of this channel in all images
	* `VECTOR_MEDIAN`: Set each pixel to the median values of the corresponding pixels.
	* `GRADIENT_MEDIAN`: Gradient median merging, using Poisson equation

## Results

Results and discussion can be found in the `Rapport`folder.
