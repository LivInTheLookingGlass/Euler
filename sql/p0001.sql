/*
 Parameters:

 Return: INT
 Purpose:
 Detailed explanation of the function which includes:
         - Function business logic
         - Transformation rules
         - Here is a bit more text.
 */
CREATE FUNCTION function_name ()
RETURNS INT
AS
BEGIN
    -- SQL statements to define the function logic
    CREATE TABLE IF NOT EXISTS threes ( value INT );
    CREATE TABLE IF NOT EXISTS fives ( value INT );
    CREATE TABLE IF NOT EXISTS fifteens ( value INT );
    DECLARE @i INT = 0;

    WHILE @i < 1000;
    BEGIN
        SET @i = @i + 3;
        INSERT INTO threes VALUES ( @i );
    END

    SET @i = 0;
    WHILE @i < 1000;
    BEGIN
        SET @i = @i + 5;
        INSERT INTO fives VALUES ( @i );
    END

    DECLARE @result INT = SELECT SUM(value) FROM threes;
    SET @result = @result + SELECT SUM(value) FROM fives;
    SET @result = @result - SELECT SUM(value) FROM threes JOIN fives WHERE threes.value = fives.value;
    DELETE threes;
    DELETE fives;
    DELETE fifteens;
    RETURN @result;
    -- Return statement indicating the result of the function
END;
