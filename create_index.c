#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>

#define BUFF_SIZE 2048
typedef uint8_t byte;

int main(int argc, char** argv) {
	uint64_t offset = 0;
	uint64_t cur=0;
	int i;
	byte buff[BUFF_SIZE];
	int cnt=BUFF_SIZE;
	FILE *data_file = fopen(argv[1], "rb");
	FILE *index_file = fopen(argv[2], "wb");

	struct stat data_stat;
	stat(argv[1], &data_stat);

	off_t data_file_size = data_stat.st_size;
	fwrite(&cur, sizeof(uint64_t), 1, index_file);
	while(offset < data_file_size) {
		if ( offset + cnt > data_file_size ) {
			cnt = data_file_size - offset;
		}
		fread(&buff, 1, cnt, data_file);
		for(int i=0; i < cnt; ++i) {
			if( buff[i] == (byte)'\n' ) {
				cur=offset+i+1;
				fwrite(&cur, sizeof(uint64_t), 1, index_file);
			}
		}
		offset+=cnt;
	}

	fclose(data_file);
	fclose(index_file);

	return 0;
}
