# Assignment 5 – Submission Structure

```text
DSA01-Assignment5-CO5/
│
├── Part_A_Design/                         # 25 marks – expanded in this update
│   ├── 00_PART_A_MASTER_INDEX.md
│   ├── README.md
│   ├── A1/
│   │   ├── 01_Task_Requirements_and_Mark_Breakdown.md
│   │   ├── 02_Complete_Design_Answer.md
│   │   ├── 03_Bill_Hierarchy.mmd
│   │   ├── 04_Alternative_Concept_and_Complexity.md
│   │   └── 05_Review_Checklist_and_Evidence.md
│   ├── A2/
│   │   ├── 01_Task_Requirements_and_Mark_Breakdown.md
│   │   ├── 02_Complete_Design_Answer.md
│   │   ├── 03_Virtual_Tables_and_Dispatch.mmd
│   │   ├── 04_Alternative_Concept_and_Complexity.md
│   │   └── 05_Prediction_Verification_and_Checklist.md
│   ├── A3/
│   │   └── [five detailed files including Payer_Hierarchy.mmd]
│   ├── A4/
│   │   └── [five detailed files including Exception_Hierarchy.mmd]
│   └── A5/
│       └── [five detailed files including Recovery_and_Unwinding.mmd]
│
├── Part_B_Implementation/                 # 25 marks – untouched
├── Submission_Admin/
├── VSCode/
├── README.md
├── BUILD_VERIFICATION.txt
└── STRUCTURE_MAP.md
```

## Part A design content

- **A1:** common bill interface, four concrete bill types, pure virtual operations, daily-total pseudocode, loop correctness, tagged-record alternative, time/space/extension comparison.
- **A2:** static and dynamic types, early/late binding, conceptual vtables, `show()` calling virtual `total()`, virtual destructor, exact prediction, undefined behaviour and `dynamic_cast` comparison.
- **A3:** abstract payer interface, SelfPay, Insurance, GovernmentScheme, explicit co-payment assumption, CorporatePayer extension, `std::function` comparison.
- **A4:** all five specified errors, custom exception hierarchy, `std::bad_alloc`, throwing/non-throwing functions, `noexcept`, destructor rule and return-code comparison.
- **A5:** catch/log/rethrow layers, `throw;`, stack unwinding, RAII, Guard output prediction and manual-cleanup comparison.

Part B is carried forward unchanged from the previous archive.
