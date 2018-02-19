DELIMITER @@
DROP TRIGGER IF EXISTS MyCustomTable_Update$$
CREATE TRIGGER MyCustomTable_Update AFTER UPDATE ON MyCustomTable FOR EACH ROW 
BEGIN
 DECLARE data VARCHAR(200);
 DECLARE return INT;
 -- concatenate strings 
 SET data = concat('columnId:',NEW.columnId);
 SET return = db_modify_event('topic://mtopic/mycustomtable.update', data);
END;
@@