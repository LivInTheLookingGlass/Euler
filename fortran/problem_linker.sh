#!/bin/bash
SRC_DIR="src"
slow_problems=()
string_problems=(0836)
OUTPUT_FILE="problems.f90"
problem_ids=()
count=0
# Loop through source files in the SRC_DIR
for file in "$SRC_DIR"/p[0-9][0-9][0-9][0-9].f90; do
    if [ -e "$file" ]; then
        # Extract problem ID from filename (assuming it's formatted like p0001.f90)
        base=$(basename "$file" .f90)
        problem_id="${base:1:4}"  # Get the number part
        problem_ids+=("$problem_id")
        ((count++))
    fi
done
problem_ids_str=$(printf '%s_i4t, &\n' "${problem_ids[@]}")
# Remove the last ', &\n' for proper formatting
length=${#problem_ids_str}
problem_ids_str=${problem_ids_str:0:length - 3}

# Start writing to the output file
cat <<EOF1 > $OUTPUT_FILE
module problems
    use constants
    use utils

EOF1
for problem_id in "${problem_ids[@]}"; do
    echo "    use Problem$problem_id" >> $OUTPUT_FILE
done

cat <<EOF2 >> $OUTPUT_FILE
    implicit none

    integer(i4t), dimension($count) :: problem_ids = (/ $problem_ids_str /)
contains

    type(AnswerT) function run_problem(problem_id) result(answer)
        integer(i4t), intent(in) :: problem_id

        answer%type = int64t
        select case (problem_id)
EOF2

for problem_id in "${problem_ids[@]}"; do
    # Check if the problem returns a string
    if [[ " ${string_problems[@]} " =~ " ${problem_id} " ]]; then
        # Handle string case
        echo "            case ($problem_id)" >> $OUTPUT_FILE
        echo "                answer%type = stringt" >> $OUTPUT_FILE
        echo "                answer%string_value = p$problem_id()" >> $OUTPUT_FILE
    else
        # Handle integer case
        echo "            case ($problem_id)" >> $OUTPUT_FILE
        echo "                answer%int_value = p$problem_id()" >> $OUTPUT_FILE
    fi
done

# Finish the function
cat <<EOF3 >> $OUTPUT_FILE
            case default
                print *, 'Unknown problem ID!'
                answer%type = errort
        end select
    end function run_problem

    pure logical function is_slow(id)
        integer(i4t), intent(in) :: id
        select case (id)
EOF3
if [ ${#slow_problems[@]} -eq 0 ]; then
    echo "            ! No slow problems defined" >> $OUTPUT_FILE
else
    echo "            case ( $(IFS=','; echo "${slow_problems[*]}") )" >> $OUTPUT_FILE
    echo "                is_slow = .true." >> $OUTPUT_FILE
fi
cat <<EOF4 >> $OUTPUT_FILE
            case default
                is_slow = .false.
        end select
    end function is_slow
end module problems
EOF4
