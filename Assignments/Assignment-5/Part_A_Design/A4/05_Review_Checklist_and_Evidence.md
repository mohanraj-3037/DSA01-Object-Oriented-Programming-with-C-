# A4 – Review Checklist and Evidence

## Error coverage checklist

- [ ] Negative charges are included.
- [ ] Claims above cover are included.
- [ ] Unknown package codes are included.
- [ ] Missing patient records are included.
- [ ] Memory allocation failure is included as `std::bad_alloc`.
- [ ] Custom billing exceptions derive from `std::exception` through a standard exception base.
- [ ] `std::bad_alloc` remains a standard-library exception rather than being misrepresented as a billing-domain error.

## Exception specification checklist

- [ ] Functions that may throw are identified.
- [ ] Destructors are non-throwing.
- [ ] Cleanup functions are non-throwing where appropriate.
- [ ] `noexcept` is used only when the implementation can satisfy it.
- [ ] The consequences of an exception escaping a `noexcept` function are explained.
- [ ] The risk of throwing during stack unwinding is explained.

## Alternative analysis checklist

- [ ] Return-code enum or result structure is described.
- [ ] Caller-side status checking is shown.
- [ ] Normal-path time is compared.
- [ ] Error-path time is compared.
- [ ] Extra result/error storage is discussed.
- [ ] Code required to propagate errors through layers is discussed.

## Evidence expected by the assignment

Submit the error list, exception class hierarchy and justified exception specifications. The Mermaid source diagram is `A4_Exception_Hierarchy.mmd` in this folder.
