#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <stdlib.h>

#define BUFF_SIZE 2048
typedef uint8_t byte;

off_t get_file_offset(FILE *index_file, long long line_num) {
	uint64_t offset;
	fseek(index_file, (line_num-1)*sizeof(uint64_t), SEEK_SET);
	fread(&offset, sizeof(uint64_t), 1, index_file);
	return offset;
}

int main(int argc, char** argv) {
	uint64_t offset = 0;
	uint64_t cur=0;
	int i;
	byte buff[BUFF_SIZE];
	int cnt=BUFF_SIZE;

	FILE *data_file = fopen(argv[1], "rb");
	FILE *index_file = fopen(argv[2], "rb");
	long long line_num = atoll(argv[3]);
	
	struct stat data_stat;
	struct stat index_stat;

	stat(argv[1], &data_stat);
	stat(argv[2], &index_stat);

	off_t data_file_size = data_stat.st_size;
	long long total_lines = index_stat.st_size / sizeof(uint64_t);

	off_t line_start = get_file_offset(index_file, line_num);
	off_t line_end = data_file_size;
	off_t position = line_start;
	if(line_num<total_lines) {
		line_end = get_file_offset(index_file, line_num+1)-1;
	}
	fseek(data_file, line_start, SEEK_SET);
	while(position < line_end) {
		if(position+cnt > line_end) {
			cnt = line_end - position;
		}

		fread(&buff, 1, cnt, data_file);
		fwrite(&buff, 1, cnt, stdout);
		position+=cnt;
	}
	printf("\n");

	fclose(data_file);
	fclose(index_file);

	return 0;
}
