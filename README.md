For https://www.linux.org.ru/forum/general/14218450

# Compile

     $ gcc create_index.c -o create_index
     $ gcc get_line.c -o get_line

# Usage

    ./create_index <data_file> <index_file>
    ./get_line <data_file> <index_file> <line_num>
    
# Example

    $ time ./create_index bigbinfile indexfile
    
    real	0m4.175s
    user	0m3.974s
    sys    0m0.201s
    
    $ time ./get_line bigbinfile indexfile 2904776
    o_2~R.96`ÑæÄkO<Óié2CýT 

    real	0m0.002s
    user	0m0.001s
    sys    0m0.001s

    $ ls -sh bigbinfile 
    1.5G bigbinfile

