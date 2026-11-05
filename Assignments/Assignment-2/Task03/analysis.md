# Q3 Analysis

The original overload set is ambiguous for a one-argument call because multiple overloads can accept it after defaults are applied. The redesigned set removes `charge(double)` and keeps one canonical kilogram overload with trailing defaults, plus exact overloads for grams (`int`) and `Parcel`.

Overload resolution prefers an exact match over a conversion. Thus `charge(2)` selects the integer-grams overload; `charge(2.0)` selects the double overload; `charge(2.0f)` converts float to double because there is no float overload. Default arguments must be trailing because omitted arguments are filled from the right.

Overload resolution occurs at compile time and has no per-call runtime cost. A small `Parcel` passed by const reference avoids copying. A single Parcel-based API scales well when adding options, while overloads make distinct input types convenient.
