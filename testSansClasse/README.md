J'aime les patates
Coucou les copains

ssh-keygen -t rsa -C "alexandre.canton-condes@etu.umontpellier.fr"
y
[Enter]
[Enter]
cat ~/.ssh/id_rsa.pub

Ensuite faut copier tout (de ssh-rsa à ton adresse email)
Rentrer cette clé dans l'encadré qu'on trouve dans Profile Setting/SSH Keys (dans le gitlab)

Puis dans le terminal :
git clone git@gitlab.info-ufr.univ-montp2.fr:e20160000668/TER_Fractale.git