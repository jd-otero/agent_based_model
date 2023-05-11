#!/bin/bash

# ###### Zona de Parámetros de solicitud de recursos a SLURM ############################
#
#SBATCH --job-name=ABM_2		#Nombre del job
#SBATCH -p short			#Cola a usar, Default=short (Ver colas y límites en /hpcfs/shared/README/partitions.txt)
#SBATCH -N 1				#Nodos requeridos, Default=1
#SBATCH -n 1				#Tasks paralelos, recomendado para MPI, Default=1
#SBATCH --cpus-per-task=1		#Cores requeridos por task, recomendado para multi-thread, Default=1
#SBATCH --mem=2000	#Memoria en Mb por CPU, Default=2048
#SBATCH --time=05:00:00			#Tiempo máximo de corrida, Default=2 horas
#SBATCH --mail-user=jd.otero10@uniandes.edu.co
#SBATCH --mail-type=ALL			
#SBATCH -o ABM_2.o%j			#Nombre de archivo de salida
#
########################################################################################

# ################## Zona Carga de Módulos ############################################
#module load  mkl/2022.01
#module load  openmpi4/4.0.5

########################################################################################


# ###### Zona de Ejecución de código y comandos a ejecutar secuencialmente #############
 ./main 2
########################################################################################

