#include "../headers/bmp_reader.h"
#include "../headers/bmp_process.h"
#include "../headers/bmp_main.h"



void bmp_main(char* argv_[]) {

	string imageName = argv_[1];
	unsigned char *header = new unsigned char[54];
	bmp_image *bi = new_bmp_image();
	bi->bh = bmp_read_header(imageName, header);
	if (bi->bh->b != B && bi->bh->m != M) {
		delete_bmp_image(bi);
		printf("The file %s is not a .bmp image\n", imageName.data());
		exit(1);
	}
	bi->bb = bmp_read_body(imageName, bi->bh->width, bi->bh->height, atoi(argv_[2]), atoi(argv_[3]), bi->bh->bits);

	bmp_to_ascii(bi);


	delete_bmp_image(bi);
	delete[] header;


}