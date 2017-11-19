#param 1 = username
dir_path="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
dir_name=$(basename $dir_path)
echo $dir_name
gitignore="$dir_path/.gitignore"
user=$1
rsync -avz --delete --exclude-from $gitignore --exclude transfer_to_grid5000.sh --exclude .gitignore --exclude '.git' -e  ssh $dir_path $user@access.grid5000.fr:grenoble
#reserve_res="oarsub -l /cpu=2,walltime=00:30:00 ./run_pdc_evol"
#access_dir="cd $dir_name"
#ssh $user@access.grid5000.fr "ssh grenoble $access_dir'&& ls && cmake . && make && '$reserve_res'&& sleep 1 && cat *.stdout'"
#echo $OAR_JOB_ID
