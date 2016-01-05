Datasets for algorithm testing    {#testdata}
==============================

While the \ref challenge_description came with a sample visitor log, for the
purpose of algorithm testing an additional set of specifically constructed
test dataset have created.


 1. Single visitor per time interval (``testdata-case1.txt``)

    Requirement: construct test data such that at any given time only a single
    visitor is present.

        08:00,09:00
        10:00,11:00
        12:00,13:00
        14:00,15:00

    Displayed as intervals on a time-axis:

          [------]      [------]      [------]      [------]

        --o------o------o------o------o------o------o------o--
        08:00  09:00  10:00  11:00  12:00  13:00  14:00  15:00


 2. Two passing visitors (``testdata-case2.txt``)

        08:00,10:00
        10:00,12:00

    Displayed as intervals on a time-axis:

          [-------------]
                        [-------------]

        --o------o------o------o------o------o------o------o--
        08:00  09:00  10:00  11:00  12:00  13:00  14:00  15:00


 3. Two simultaneous visitors (``testdata-case3.txt``)

        08:00,10:00
        09:00,11:00

    Displayed as intervals on a time-axis:

          [-------------]
                 [-------------]

        --o------o------o------o------o------o------o------o--
        08:00  09:00  10:00  11:00  12:00  13:00  14:00  15:00


 4. (``testdata-case4.txt``)

        08:00,11:00
        10:00,13:00
        12:00,15:00

    Displayed as intervals on a time-axis:

          [--------------------]
                        [--------------------]
                                      [--------------------]

        --o------o------o------o------o------o------o------o--
        08:00  09:00  10:00  11:00  12:00  13:00  14:00  15:00


 5. Build-up and turnover of visitors (``testdata-case5.txt``)

        08:00,11:00
        09:00,12:00
        10:00,13:00

    Displayed as intervals on a time-axis:

          [--------------------]
                 [--------------------]
                        [--------------------]

        --o------o------o------o------o------o------o------o--
        08:00  09:00  10:00  11:00  12:00  13:00  14:00  15:00
