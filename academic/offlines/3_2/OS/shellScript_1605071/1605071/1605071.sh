#!/bin/bash

if [ $# -eq 0 ]; then
	echo "please run the script as: $0 input_file_name"
	exit

elif [ $# -eq 1 ] ; then    
    file_ext=$(echo $1 | cut -d "." -f 2)
    if [ $file_ext != "txt" ]
    then
        echo "please run the script as: $0 input_file_name"
	    exit
    else
        argNo=1
        working_dir=$(pwd)
        input=$1
    fi
elif [ $# -eq 2 ] ; then
    argNo=2
    working_dir=$1
    input=$2
fi

#echo "working directory"
#echo $working_dir
#echo $input

if [ $argNo -eq 1 ]
then
    rm -r ../myoutput.csv
    rm -r ../myoutput_dir
    mkdir ../myoutput_dir   
    my_csv="$(realpath ../myoutput.csv)"
    #echo "my_csv"
    #echo $my_csv

    output_dir_path="$(realpath ../myoutput_dir)"
    #echo "output_dir_path"
    #echo $output_dir_path
elif [ $argNo -eq 2 ]
then
    : '
    rm -r ~/checkoutput.csv
    rm -r ~/myoutput_dir
    mkdir ~/myoutput_dir
    my_csv=~/checkoutput.csv

    output_dir_path=~/myoutput_dir
    '
    parent_dir="$(dirname "$1")"
    rm -r ${parent_dir}/myoutput_dir
    mkdir ${parent_dir}/myoutput_dir

    rm -r ${parent_dir}/myoutput.csv
    my_csv=${parent_dir}/myoutput.csv

    output_dir_path=${parent_dir}/myoutput_dir

fi


#root="$(realpath .)"
root="$(realpath "$working_dir")"
root_path_length=${#root} 
((root_path_length=root_path_length+2))
#echo "root_path"
#echo $root
#echo $root_path_length
base_root="${root##*/}"
#echo "base_root_path"
#echo $base_root
#echo "remove_from_root"
remove_from_root="${root%/*$base_root}"
#echo $remove_from_root
#echo $base_root $remove_from_root
remove_from_root_length=${#remove_from_root}
((remove_from_root_length=remove_from_root_length+2))
#echo "remove_from_root_length"
#echo $remove_from_root_length

cmd=$(head -n 1 "$input" | tail -n 1)
nol=$(head -n 2 "$input" | tail -n 1)
word_to_search=$(head -n 3 "$input" | tail -n 1)

#echo $cmd
#echo $nol
#echo $word_to_search

if [ $cmd = "begin" ]
then
    temp_cmd=head
elif [ $cmd = "end" ]
then
    temp_cmd=tail
fi

#echo $temp_cmd


traverse_directories()
{
    cd "$1"

    for f in *
    do 
        if [ -d "$f" ]; then
            traverse_directories "$f"

        
        elif [ -f "$f" ]; then
            if file "$f" | grep -q text ; then
                if $temp_cmd -n $nol $f | grep -qi $word_to_search; then
                    #echo "HERE"
                    #echo "in 1st if"
                    #echo $f
                    fn="${f%.*}"
                    f_length=${#f}
                    #echo "f_length"
                    #echo $f_length

                    ext="${f##*.}"

					#line_no=$($temp_cmd -n $nol $f | grep -ni $word_to_search | cut -f1 -d':')
                    line_no=$(grep -in $word_to_search $f | $temp_cmd -n 1 | cut -f1 -d':')

                    str=$(grep -in $word_to_search $f | $temp_cmd -n 1 | cut -f2 -d':')

                    this_path="$(realpath $f)"
                    #echo "this path"
                    #echo $this_path
                    this_path_length=${#this_path}
                    #echo "this_path_length"
                    #echo $this_path_length

                    #using for csv file
                    #temp_path=$(echo $this_path | cut -c$root_path_length-$this_path_length)
                    temp_path=$(echo $this_path | cut -c$remove_from_root_length-$this_path_length)
                    #echo "temp_path"
                    #echo $temp_path
                    temp_path_length=${#temp_path}
                    #echo "temp_path_length"
                    #echo $temp_path_length

                    ((result=$temp_path_length-$f_length-1))
                    #echo "result"
                    #echo $result

                    if [ $result -gt 0 ]
                    then
                        req_path=$(echo $temp_path | cut -c1-$result)
                    fi
                    #echo "req_path"
                    #echo $req_path

                    dir=$(echo $req_path | tr / .)
                    #echo "directory"
                    #echo "$dir"

                    if [ -z "$req_path" ]
                    then
                        if [ "$fn" != "$ext" ]
                        then
                            new_file_name="${fn}_${line_no}.${ext}"
                        else
                            new_file_name="${fn}_${line_no}"
                        fi
                    else
                        if [ "$fn" != "$ext" ] 
                        then
                            new_file_name="${dir}.${fn}_${line_no}.${ext}"
                        else
                            new_file_name="${dir}.${fn}_${line_no}"
                        fi
                    fi

                    file_line_count=$(cat $f | wc -l)
                    #echo "total_line_in_file"
                    #echo $file_line_count
                    loop_count=$($temp_cmd -n $nol $f | grep -ci $word_to_search)
                    #echo "$temp_path"
                    #echo "$loop_count"
                    #echo "csv_line_no"

                    for((i=1;i<=$loop_count;i++))
                    do
                        temp_line_no=$($temp_cmd -n $nol $f | grep -ni $word_to_search | head -n $i | tail -n 1 | cut -f1 -d':')
                        csv_str=$($temp_cmd -n $nol $f | grep -ni $word_to_search | head -n $i | tail -n 1 | cut -f2 -d':')
                      
                        if [ $temp_cmd  = "tail" ] && [ $file_line_count -ge $nol ]
                        then
                            ((csv_line_no=$file_line_count-$nol+$temp_line_no))
                        else
                            csv_line_no=$temp_line_no
                        fi

                        #echo "$csv_line_no"

                        echo "$temp_path,$csv_line_no,\"$csv_str\"" >>"$my_csv"     

                    done

                    #echo "$temp_path,$line_no,$str" >>"$my_csv"
                    
                    #new_file_name="${fn}_${line_no}.${ext}"
                    cp $f "${output_dir_path}/${new_file_name}"
                fi
            else 
                echo $f is a non text file
            fi 
        
        fi
    done

    cd ../
}

#traverse_directories .
#cd ..; my_csv="$(realpath .)/myoutput.csv"
echo "File Path,Line Number,Line Containing Searched String" >>"$my_csv" 

traverse_directories "$working_dir"

echo
echo
echo
cd "$output_dir_path"
file_count=$(ls -1 | wc -l)
echo "file_count: " $file_count
#echo $file_count
