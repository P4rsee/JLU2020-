# ListOperator

## 声明：本文件中的链表操作全部默认链表以一个数据域无效的结点为头指针（即哨兵结点）

### *void* pushBackDiagnosisList(DiagnosisRecord* head, DiagnosisRecord* newRecord)

​	第一个参数是诊疗记录链表的头指针，第二个参数是要插入的新结点的指针，该函数读取newRecord中的数据构造一个新结点，向链表最后插入新结点。

### *bool* deleteDiagnosisList(DiagnosisRecord *head, *int* queryId)

​	第一个参数是诊疗记录的表头，第二个参数是要删除的结点的患者ID。若删除成功返回true，反之返回false。

### *void* pushBackCheckList(CheckInfo* head,CheckInfo * newCheck)

​	第一个参数是检查记录链表的头指针，第二个参数是要插入的新结点的指针，该函数读取newCheck中的数据构造一个新结点，向链表最后插入新结点。

### *void* pushBackPrescribeList(PrescribeInfo* head, PrescribeInfo* newPrescribe)

​	第一个参数是开药记录链表的头指针，第二个参数是要插入的新结点的指针，该函数读取newPrescribe中的数据构造一个新结点，向链表最后插入新结点。

### *void* pushBackDoctorList(DoctorNode* head, DoctorNode* newDoctorNode)

​		第一个参数是医生链表的头指针，第二个参数是要插入的新结点的指针，该函数读取newDoctorNode中的数据构造一个新结点，向链表最后插入新结点。

### DiagnosisRecord* queryDiagnosisBySectionId(DiagnosisRecord* head,*int* sectionId)

​	第一个参数是诊疗记录链表的头指针，第二个参数是科室ID，该函数遍历以head为头指针的链表，查找所有科室ID为sectionID的诊疗记录，把他们按照在原链表中出现的顺序生成新的链表，并返回新链表的头指针。

### DiagnosisRecord* queryDiagnosisByDoctorId(DiagnosisRecord* head, *int* doctorId)

​	第一个参数是诊疗记录链表的头指针，第二个参数是医生ID，该函数遍历以head为头指针的链表，查找所有医生ID为doctorId的诊疗记录，把他们按照在原链表中出现的顺序生成新的链表，并返回新链表的头指针。

### DiagnosisRecord* queryDiagnosisByRegisterId(DiagnosisRecord* head,*int* registerId)

​	第一个参数是诊疗记录链表的头指针，第二个参数是患者ID。该函数查找患者ID为registerId的诊疗记录,找到后新建一个结点指针并返回该指针。

### DiagnosisRecord* findModifiedNode(DiagnosisRecord* head,*int* registerId)

​	第一个参数是诊疗记录链表的头指针，第二个参数是患者ID。该函数查找患者ID为registerId的诊疗记录，找到后直接返回该结点的指针（可以直接从该指针对链表中的原结点进行修改）。

### *void* pushbackWard(Ward* head,Ward* newWard)

​			第一个参数是病房链表的头指针，第二个参数是要插入的新结点的指针，该函数读取newWard中的数据构造一个新结点，向链表最后插入新结点。

### *bool* modifyWard(Ward *head, *int* wardId, Ward *newWard)

​		第一个参数是病房链表的头指针，第二个参数是要修改的病房结点的Id，第三个参数是要修改为的新结点的指针。该函数把病房Id为wardId的病房数据修改为newWard中的数据，成功返回Ture,否则返回False。