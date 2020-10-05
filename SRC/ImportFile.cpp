#include"ImportFile.h";

void FileInput() {  // 从文件导入诊疗记录
    char writePath[] = "out.txt";
    char readPath[] = "in.txt";
    //scanf("%s", readPath);
    FILE* fileReadPointer, * fileWritePointer;
    while ((fileReadPointer = fopen(readPath, "r")) == NULL) {
        printf("文件路径不正确,请重新输入!\n");
        scanf("%s", readPath);
    }
    fileWritePointer = fopen(writePath, "w");
    while (!feof(fileReadPointer)) {
        printf("开始读入\n");
        DiagnosisRecord* nowRecord = InRecord(fileReadPointer);
        printf("读入结束\n");
        if (!nowRecord)continue;
        printf("读入成功,开始写入\n");
        OutRecord(fileWritePointer, nowRecord);
        printf("写入完毕\n");
    }
    return;
}

/*int main(void) {
    //system("chcp 65001");
    FileInput();
    return 0;
}*/
