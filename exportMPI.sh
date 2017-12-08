#installed using http://lsi.ugr.es/jmantas/pdp/ayuda/datos/instalaciones/Install_OpenMPI_en.pdf
# Use -LLIBDIR
echo "Call to exportMPI.sh"
export PATH="$PATH:/home/$USER/.ompi/bin"
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/home/$USER/.ompi/lib64/"
export CMAKE_PREFIX_PATH="$CMAKE_PREFIX_PATH:/home/sbelletier/.ompi/"

#Note : exec using mpirun
#Exemple
#mpirun -np 4 pdc_evol_model

