## DoctorInfoProcessor

### void generateRegisterID(DiagnosisRecord* DiagnosisRecordPtr)

​	传入一个没有赋值挂号号码的诊疗记录指针，给其赋值一个挂号号码。

### DoctorNode* getRecommendedDoctors(DoctorNode *head,int sectionId)

​	第一个参数是医生链表的头指针，第二个参数是选定的科室，返回一个按推荐度降序排序的医生链表。

### void freeRecommendedDoctors(DoctorNode* head)

​	传入一个医生链表的头指针，释放整条链表的空间。

### void combineDoctorIntoDiagnosisRecord(DiagnosisRecord* head,DiagnosisRecord \*currentRecordPtr, DoctorNode* newDoctorPtr)

​	传入一个诊疗记录的头指针，一个医生记录未赋值的诊疗记录结点，一个医生结点的指针，该函数把医生结点的信息赋值给诊疗记录，并将其并入诊疗记录链表。

