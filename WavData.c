#include <stdlib.h>
#include <stdio.h>
#define LONGLONG long long
#define BUFSIZE 65536
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif
const char* IAERR = "ERROR: Invalid argument [%s]\n\n";
const char* IFERR = "ERROR: Could not open input file.\n";
const char* OFERR = "ERROR: Could not open output file.\n";
const char* TAERR = "ERROR: Too many arguments.\n\n";
short readInt16(FILE* f) {
	short v = 0;
	v |= fgetc(f);
	v |= fgetc(f) << 8;
	return v;
}
int readInt32(FILE* f) {
	int v = 0;
	v |= fgetc(f);
	v |= fgetc(f) << 8;
	v |= fgetc(f) << 16;
	v |= fgetc(f) << 24;
	return v;
}
void writeInt16(FILE* f, short d) {
	fputc(d&255, f);
	fputc((d>>8)&255, f);
}
void writeInt32(FILE* f, int d) {
	fputc(d&255, f);
	fputc((d>>8)&255, f);
	fputc((d>>16)&255, f);
	fputc((d>>24)&255, f);
}
long int streamSize(FILE* f) {
	long int c,s;
	c = ftell(f);
	fseek(f, 0, SEEK_END);
	s = ftell(f);
	fseek(f, c, SEEK_SET);
	return s;
}
char* fmtString(short fmt) {
	switch(fmt) {
		case 0x0: return "Unknown";
		case 0x1: return "PCM";
		case 0x2: return "Microsoft ADPCM";
		case 0x3: return "IEEE float";
		case 0x4: return "Conpaq Computer VSELP";
		case 0x5: return "IBM CVSD";
		case 0x6: return "8-bit ITU-T G.711 A-law";
		case 0x7: return "8-bit ITU-T G.711 µ-law";
		case 0x10: return "OKI ADPCM";
		case 0x11: return "Intel DVI ADPCM";
		case 0x12: return "Videologic Mediaspace ADPCM";
		case 0x13: return "Sierra ADPCM";
		case 0x14: return "G.723 ADPCM";
		case 0x15: return "DSP Solutions DIGISTD";
		case 0x16: return "DSP Solutions DIGIFIX";
		case 0x17: return "Dialogic OKI ADPCM";
		case 0x18: return "MediaVision ADPCM";
		case 0x19: return "Hewlet-Packard CU Codec";
		case 0x20: return "Yamaha ADPCM";
		case 0x21: return "Speech Compression SONARC";
		case 0x22: return "DSP Group TrueSpeech";
		case 0x23: return "Echo Speech EchoSC1";
		case 0x24: return "Audiofile AF36";
		case 0x25: return "Audio Processing Technology APTX";
		case 0x26: return "Audiofile AF10";
		case 0x27: return "Prosody 1612";
		case 0x28: return "Mergine Technologies LRC";
		case 0x30: return "Dolby AC2";
		case 0x31: return "Microsoft GSM610";
		case 0x32: return "Microsoft MSN Audio";
		case 0x33: return "Antex ADPCME";
		case 0x34: return "Control Resources VQLPC";
		case 0x35: return "DSP Solutions DIGIREAL";
		case 0x36: return "DSP Solutions DIGIADPCM";
		case 0x37: return "Control Resources CR10";
		case 0x38: return "Natural MicroSystems VBXADPCM";
		case 0x39: return "Crystal Semiconductor IMA ADPCM"; /* Roland RDAC? */
		case 0x3A: return "Echo Speech EchoSC3";
		case 0x3B: return "Rockwell ADPCM";
		case 0x3C: return "Rockwell DigiTalk";
		case 0x3D: return "Xebec Multimedia";
		case 0x40: return "Antex G.721 ADPCM";
		case 0x41: return "Antex G.728 CELP";
		case 0x42: return "Microsoft MSG723";
		case 0x50: return "Microsoft MPEG";
		case 0x52: return "Insoft RT24";
		case 0x53: return "Insoft PAC";
		case 0x55: return "ISO MPEG Layer 3";
		case 0x59: return "Lucent G.723";
		case 0x60: return "Cirrus";
		case 0x61: return "ESS Technology ESPCM";
		case 0x62: return "Voxware";
		case 0x63: return "Canopus ATRAC";
		case 0x64: return "APICOM G.726 ADPCM";
		case 0x65: return "APICOM G.722 ADPCM";
		case 0x66: return "Microsoft DSAT";
		case 0x67: return "Microsoft DSAT Display";
		case 0x69: return "Voxware Byte Aligned";
		case 0x70: return "Voxware AC8";
		case 0x71: return "Voxware AC10";
		case 0x72: return "Voxware AC16";
		case 0x73: return "Voxware AC20";
		case 0x74: return "Voxware MetaVoice RT24";
		case 0x75: return "Voxware MetaSound RT29";
		case 0x76: return "Voxware RT29HW";
		case 0x77: return "Voxware VR12";
		case 0x78: return "Voxware VR18";
		case 0x79: return "Voxware TQ40";
		case 0x80: return "Softsound";
		case 0x81: return "Voxware TQ60";
		case 0x82: return "MSRT24";
		case 0x83: return "G.729A";
		case 0x84: return "MVI MV12";
		case 0x85: return "DataFusion G.726";
		case 0x86: return "DataFusion GSM 610";
		case 0x88: return "ISI Audio";
		case 0x89: return "Online";
		case 0x91: return "SBC24";
		case 0x92: return "Dolby AC3 SPDIF";
		case 0x97: return "ZyXEL ADPCM";
		case 0x98: return "Philips LPCBB";
		case 0x99: return "Packed";
		case 0x100: return "Rhetorex ADPCM";
		case 0x101: return "BeCubed Software IRAT";
		case 0x111: return "Vivo G.723";
		case 0x112: return "Vivo Siren";
		case 0x123: return "Digital G.723";
		case 0x200: return "Creative ADPCM";
		case 0x202: return "Creative Labs FastSpeech 8";
		case 0x203: return "Creative Labs FastSpeech 10";
		case 0x220: return "Quarterdeck";
		case 0x300: return "Fujitsu FM_TOWNS_SND";
		case 0x400: return "Brooktree BTV Digital";
		case 0x680: return "VME VMPCM";
		case 0x1000: return "Olivetti GSM";
		case 0x1001: return "Olivetti ADPCM";
		case 0x1002: return "Olivetti CELP";
		case 0x1003: return "Olivetti SBC";
		case 0x1004: return "Olivetti OPR";
		case 0x1100: return "Lernout & Hauspie Codec";
		case 0x1400: return "Norric Communications Audio";
		case 0x1401: return "ISI Audio";
		case 0x1500: return "Soundspace Music Compression";
		case 0x2000: return "DVM";
		case (short)0xFFFE: return "Extensible wave";
		case (short)0xFFFF: return "Development Format"; /* Format in development */
		default: return "Invalid";
	}
}
void printChannelMask(int msk) {
	int f = 1;
	if(msk & 0x1) { if(f) f = 0; else putchar(','); printf("FRONT_LEFT"); }
	if(msk & 0x2) { if(f) f = 0; else putchar(','); printf("FRONT_RIGHT"); }
	if(msk & 0x4) { if(f) f = 0; else putchar(','); printf("FRONT_CENTER"); }
	if(msk & 0x8) { if(f) f = 0; else putchar(','); printf("LOW_FREQUENCY"); }
	if(msk & 0x10) { if(f) f = 0; else putchar(','); printf("BACK_LEFT"); }
	if(msk & 0x20) { if(f) f = 0; else putchar(','); printf("BACK_RIGHT"); }
	if(msk & 0x40) { if(f) f = 0; else putchar(','); printf("FRONT_LEFT_OF_CENTER"); }
	if(msk & 0x80) { if(f) f = 0; else putchar(','); printf("FRONT_RIGHT_OF_CENTER"); }
	if(msk & 0x100) { if(f) f = 0; else putchar(','); printf("BACK_CENTER"); }
	if(msk & 0x200) { if(f) f = 0; else putchar(','); printf("SIDE_LEFT"); }
	if(msk & 0x400) { if(f) f = 0; else putchar(','); printf("SIDE_RIGHT"); }
	if(msk & 0x800) { if(f) f = 0; else putchar(','); printf("TOP_CENTER"); }
	if(msk & 0x1000) { if(f) f = 0; else putchar(','); printf("TOP_FRONT_LEFT"); }
	if(msk & 0x2000) { if(f) f = 0; else putchar(','); printf("TOP_FRONT_CENTER"); }
	if(msk & 0x4000) { if(f) f = 0; else putchar(','); printf("TOP_FRONT_RIGHT"); }
	if(msk & 0x8000) { if(f) f = 0; else putchar(','); printf("TOP_BACK_LEFT"); }
	if(msk & 0x10000) { if(f) f = 0; else putchar(','); printf("TOP_BACK_CENTER"); }
	if(msk & 0x20000) { if(f) f = 0; else putchar(','); printf("TOP_BACK_RIGHT"); }
}
int wavToData(FILE* fin, FILE* fout) {
	int len,bsz,err=0,go=1,tmp;
	char buf[BUFSIZE];
	while(go) {
		go = 0;
		/* Verify wave header */
		if(readInt32(fin) != 0x46464952) { err = 1; break; }
		readInt32(fin);
		if(readInt32(fin) != 0x45564157) { err = 1; break; }
		if(readInt32(fin) != 0x20746D66) { err = 1; break; }
		/* Skip the format chunk */
		fseek(fin, readInt32(fin), SEEK_CUR);
		/* Find the data chunk */
		while(1) {
			tmp = readInt32(fin);
			if(tmp == -1) { err = 1; break; }
			if(tmp == 0x61746164) break;
			if((tmp = readInt32(fin)) < 0) { err = 1; break; }
			fseek(fin, tmp, SEEK_CUR);
		}
		if(err) break;
		/* Read stream length */
		len = readInt32(fin);
		/* Copy data chunk */
		while(len > 0) {
			if((bsz = fread(buf, 1, min(BUFSIZE, len), fin)) < 1) break;
			fwrite(buf, 1, bsz, fout);
			len -= bsz;
		}
	}
	fflush(fout);
	return err;
}
int dataToWavEx(FILE* fin, FILE* fout, short channels, int sampleRate, short bitsPerSample, short audioType) {
	int len;
	long int length = streamSize(fin);
	short blockAlign = (short)(((int)channels * (int)bitsPerSample) >> 3);
	int byteRate, extra, dataSize;
	char buf[BUFSIZE];
	if(blockAlign == 0) blockAlign = 1;
	byteRate = (int)(((LONGLONG)channels * (LONGLONG)bitsPerSample * (LONGLONG)sampleRate) >> 3);
	extra = (blockAlign - ((short) (length % ((int) blockAlign)))) % blockAlign;
	dataSize = length + extra;
	if(dataSize & 1) { ++extra; ++dataSize; }
	/* Write RIFF header */
	writeInt32(fout, 0x46464952); /* RIFF */
	writeInt32(fout, dataSize + 36); /* Chunk Size (8-filesize, or 36+datasize) */
	writeInt32(fout, 0x45564157); /* WAVE (format specifier) */
	/* Write FMT chunk */
	writeInt32(fout, 0x20746D66); /* fmt (chunk header) */
	writeInt32(fout, 16); /* fmt chunk size */
	writeInt16(fout, audioType); /* Audio type (1=PCM) */
	writeInt16(fout, channels); /* number of channels */
	writeInt32(fout, sampleRate); /* sample rate (hz) */
	writeInt32(fout, byteRate); /* byterate (bytes/s) */
	writeInt16(fout, blockAlign); /* block align (bytes per frame) */
	writeInt16(fout, bitsPerSample); /* bits per sample (bit depth) */
	/* Write data chunk */
	writeInt32(fout, 0x61746164); /* data (chunk header) */
	writeInt32(fout, dataSize); /* data chunk size */
	while((len = fread(buf, 1, BUFSIZE, fin)) > 0) fwrite(buf, 1, len, fout);
	while(extra > 0) { fputc(0, fout); --extra; }
	fflush(fout);
	return 0;
}
int dataToWav(FILE* fin, FILE* fout, short channels, int sampleRate, short bitsPerSample) {
	return dataToWavEx(fin, fout, channels, sampleRate, bitsPerSample, (short)1);
}
int wavInfo(FILE* fin) {
	int br,sk,cm;
	short fm;
	/* Ensure input is a proper wave file */
	if(readInt32(fin) != 0x46464952) return 1;
	printf("Wave Size    : %d\n", readInt32(fin));
	if(readInt32(fin) != 0x45564157) return 1;
	if(readInt32(fin) != 0x20746D66) return 1;
	/* Write standard wave information */
	sk = readInt32(fin);
	fm = (int)readInt16(fin);
	printf("Audio Type   : %d [%s]\n", (int)fm, fmtString(fm));
	printf("Channel Count: %d\n", (int)readInt16(fin));
	printf("Sample Rate  : %d hz\n", readInt32(fin));
	printf("Data Rate    : %d bytes/s\n", br = readInt32(fin));
	printf("Bitrate      : %d kbps\n", (br << 3) / 1000);
	printf("Block Align  : %d bytes\n", (int)readInt16(fin));
	printf("Bit Depth    : %d bits\n", (int)readInt16(fin));
	/* Write extra wave information */
	if(sk >= 18) {
		fm = readInt16(fin);
		if(fm != (sk - 18)) return 1;
		if(fm == 22) {
			printf("Valid S. Bits: %d bits\n", (int)readInt16(fin));
			printf("Channel Mask : %04x [", cm = readInt32(fin)); printChannelMask(cm); printf("]\n");
			printf("Subformat    : ");
			for(fm = 0; fm < 16; ++fm) printf("%02x", (int)fgetc(fin));
		}
	}
	if(br > 0) {
		fseek(fin, sk + 20, SEEK_SET);
		/* Seek to data chunk */
		while(1) {
			sk = readInt32(fin);
			if(sk == -1) return 0;
			if(sk == 0x61746164) break;
			if(sk == 0x74636166) {
				/* Handle fact chunk */
				if((sk = readInt32(fin)) < 0) return 1;
				if(sk > 4) {
					printf("Sample Count : %d\n", readInt32(fin));
					sk -= 4;
				}
				fseek(fin, sk - 4, SEEK_CUR);
			} else {
				/* Skip to the next chunk */
				if((sk = readInt32(fin)) < 0) return 1;
				fseek(fin, sk, SEEK_CUR);
			}
		}
		/* Write data statistics */
		sk = readInt32(fin);
		printf("Data Size    : %d bytes\n", sk);
		printf("Play Length  : %02d:%02d:%02d.%03d\n", (sk / br) / 3600, ((sk / br) / 60) % 60, (sk / br) % 60, (int)(((LONGLONG)sk * (LONGLONG)1000) / (LONGLONG)br) % 1000);
	}
	return 0;
}
int riffInfo(FILE* fin) {
	int cn,cs;
	if(readInt32(fin) != 0x46464952) return 1;
	printf("RIFF [%d bytes", readInt32(fin));
	cn = readInt32(fin);
	printf(" of type %c%c%c%c]\n", (char)(cn & 255), (char)((cn >> 8) & 255), (char)((cn >> 16) & 255), (char)((cn >> 24) & 255));
	while((cn = readInt32(fin)) != -1) {
		cs = readInt32(fin);
		printf("  %c%c%c%c [%d bytes]\n", (char)(cn & 255), (char)((cn >> 8) & 255), (char)((cn >> 16) & 255), (char)((cn >> 24) & 255), cs);
		if(cs < 0) break;
		fseek(fin, cs, SEEK_CUR);
	}
	return 0;
}
void printHelp(void) {
	printf("usage: WavData [e|d] [options] [infile] [outfile]\n");
	printf("       WavData [i|r] [infile]\n\n");
	printf("modes:\n");
	printf("   e     - Convert data to wav\n");
	printf("   d     - Convert wav to data\n");
	printf("   i     - Show wav information\n");
	printf("   r     - Show riff information\n\n");
	printf("options:\n");
	printf("   -c#   - Sets the number of channels (1-32, default 1)\n");
	printf("   -d#   - Sets the bit depth (8-32, default 16)\n");
	printf("   -r#   - Sets the sample rate (4000-192000, default 44100)\n");
	printf("   -f#   - Sets the wave data format (1, default 1)\n");
	printf("   --    - Stop scanning command line for options\n");
}
int main(int argc, char** argv) {
	FILE *fi,*fo;
	short cc = 1, bd = 16, wf = 1;
	int sr = 44100,rc,idx = 2;
	if(argc < 3) {
		printHelp();
		return 1;
	} else {
		if(argv[1][0] == 'e') {
			while(idx < argc) {
				if(argv[idx][0] == '-') {
					switch(argv[idx][1]) {
						case 'c': cc = (short)atoi(argv[idx] + 2); if(!cc) { fprintf(stderr, IAERR, argv[idx]); printHelp(); return 1; } break;
						case 'd': bd = (short)atoi(argv[idx] + 2); if(!bd) { fprintf(stderr, IAERR, argv[idx]); printHelp(); return 1; } break;
						case 'r': sr = atoi(argv[idx] + 2); if(!sr) { fprintf(stderr, IAERR, argv[idx]); printHelp(); return 1; } break;
						case 'f': wf = atoi(argv[idx] + 2); if(!wf) { fprintf(stderr, IAERR, argv[idx]); printHelp(); return 1; } break;
						case '-': break;
						default:
							fprintf(stderr, IAERR, argv[idx]);
							printHelp();
							return 1;
					}
					if(argv[idx][1] == '-') { ++idx; break; }
				} else {
					break;
				}
				++idx;
			}
			if(idx > (argc - 2)) {
				printHelp();
				return 1;
			}
			if(idx < (argc - 2)) {
				fprintf(stderr, TAERR);
				printHelp();
				return 1;
			}
			if(bd < 1) bd = 16;
			if(bd == 1) bd &= -8;
			if(cc < 1) cc = 1;
			if(sr < 1) sr = 44100;
			if(!(fi = fopen(argv[idx], "rb"))) { fprintf(stderr, IFERR); return 1; }
			if(!(fo = fopen(argv[idx+1], "wb"))) { fclose(fi); fprintf(stderr, OFERR); return 1; }
			if(rc = dataToWavEx(fi, fo, cc, sr, bd, wf)) fprintf(stderr, "ERROR: Failed to convert data into wave file.\n");
			fclose(fi);
			fclose(fo);
			return rc;
		} else if(argv[1][0] == 'd') {
			if(argc < 4) { printHelp(); return 1; }
			if(argc > 4) { fprintf(stderr, TAERR); printHelp(); return 1; }
			if(!(fi = fopen(argv[2], "rb"))) { fprintf(stderr, IFERR); return 1; }
			if(!(fo = fopen(argv[3], "wb"))) { fprintf(stderr, OFERR); return 1; }
			if(rc = wavToData(fi, fo)) fprintf(stderr, "ERROR: Invalid wave file.\n");
			fclose(fi);
			fclose(fo);
			return rc;
		} else if(argv[1][0] == 'i') {
			if(argc < 3) { printHelp(); return 1; }
			if(argc > 3) { fprintf(stderr, TAERR); printHelp(); return 1; }
			if(!(fi = fopen(argv[2], "rb"))) { fprintf(stderr, IFERR); return 1; }
			if(rc = wavInfo(fi)) fprintf(stderr, "ERROR: Invalid wave file.\n");
			fclose(fi);
			return rc;
		} else if(argv[1][0] == 'r') {
			if(argc < 3) { printHelp(); return 1; }
			if(argc > 3) { fprintf(stderr, TAERR); printHelp(); return 1; }
			if(!(fi = fopen(argv[2], "rb"))) { fprintf(stderr, IFERR); return 1; }
			if(rc = riffInfo(fi)) fprintf(stderr, "ERROR: Invalid RIFF file.\n");
			fclose(fi);
			return rc;
		} else {
			printHelp();
			return 1;
		}
	}
}
