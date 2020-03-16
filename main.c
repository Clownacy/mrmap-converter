/*
 *  zlib License
 *
 *  (C) 2019-2020 Clownacy
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty.  In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *  1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *  2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *  3. This notice may not be removed or altered from any source distribution.
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("\nstage.tbl to mrmap.bin converter by Clownacy\n\nUsage: %s [input filename] [output filename]\n\n", argv[0]);
	}
	else
	{
		const char *in_filename = argc > 1 ? argv[1] : "stage.tbl";
		const char *out_filename = argc > 2 ? argv[2] : "mrmap.bin";

		FILE *in_file = fopen(in_filename, "rb");

		if (in_file == NULL)
		{
			printf("Error - could not open `%s`\n", in_filename);
		}
		else
		{
			// Load input file to memory
			fseek(in_file, 0, SEEK_END);
			const size_t in_file_size = ftell(in_file);
			rewind(in_file);
			unsigned char *in_file_buffer = malloc(in_file_size);
			fread(in_file_buffer, 1, in_file_size, in_file);
			fclose(in_file);

			FILE *out_file = fopen(out_filename, "wb");

			if (out_file == NULL)
			{
				printf("Error - could not open `%s`\n", out_filename);
			}
			else
			{
				// Write 'mrmap.bin' header
				const size_t entry_count = in_file_size / 0xE5;
				fputc((entry_count >> (8 * 0)) & 0xFF, out_file);
				fputc((entry_count >> (8 * 1)) & 0xFF, out_file);
				fputc((entry_count >> (8 * 2)) & 0xFF, out_file);
				fputc((entry_count >> (8 * 3)) & 0xFF, out_file);

				// Convert each room entry from 'stage.tbl' format to 'mrmap.bin'
				for (size_t i = 0; i < entry_count; ++i)
				{
					const unsigned char *table_entry = &in_file_buffer[i * 0xE5];

					fwrite(&table_entry[0], 1, 0x10 - 1, out_file);
					fputc(0, out_file);
					fwrite(&table_entry[0x20], 1, 0x10 - 1, out_file);
					fputc(0, out_file);
					fputc(table_entry[0x40], out_file);
					fwrite(&table_entry[0x44], 1, 0x10 - 1, out_file);
					fputc(0, out_file);
					fwrite(&table_entry[0x64], 1, 0x10 - 1, out_file);
					fputc(0, out_file);
					fwrite(&table_entry[0x84], 1, 0x10 - 1, out_file);
					fputc(0, out_file);
					fputc(table_entry[0xA4], out_file);
					fwrite(&table_entry[0xC5], 1, 0x20 - 1, out_file);
					fputc(0, out_file);
					fputc(0, out_file);
					fputc(0, out_file);
				}

				fclose(out_file);
			}

			free(in_file_buffer);
		}
	}
}
