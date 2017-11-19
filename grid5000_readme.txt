#Obtenir accè grid5000
# suivre indications: https://moodle.insa-lyon.fr/course/view.php?id=3958
#Générer une clé public et privé qui se trouve dans .ssh. Remplir la phrase passphrase
ssh-keygen -t rsa


#transférer les modifications vers grid5000:
./transfer_to_grid5000.sh <user>


#connection à grid5000
ssh <user>@access.grid5000.fr
ssh grenoble (ou autre site)

#Réserver resources:
#1 node:
oarsub -I

#2 core:
oarsub -l core=1 -I

#2cpu:
oarsub -l cpu=1 -I
