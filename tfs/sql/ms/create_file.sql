drop procedure create_file;
delimiter $$
create procedure
create_file(in i_app_id bigint, in i_uid bigint,
  in i_ppid bigint unsigned, in i_pid bigint unsigned, in i_pname varbinary(512),
  in i_name varbinary(512))
begin
    declare aff_row int;
    declare o_ret bigint;
    declare exit handler for sqlexception
    begin
        set o_ret = -14001;
        rollback;
        select o_ret;
    end;
    select 0 into aff_row;
    select -14000 into o_ret;
    start transaction;
    update t_meta_info set modify_time = now()
    where app_id = i_app_id and uid = i_uid and pid = i_ppid and name = i_pname;
    select count(1) into aff_row from t_meta_info
    where app_id = i_app_id and uid = i_uid and pid = i_ppid and name = i_pname;
    if aff_row = 1 then
      insert into t_meta_info (app_id, uid, pid , name, id, create_time, modify_time, size, ver_no)
      values (i_app_id, i_uid, i_pid | (1 << 63), i_name, 0, now(), now(), 0, 1);
      select row_count() into aff_row;
      set o_ret = 1;
    else
      set o_ret = -14002;
    end if;
    if o_ret <= 0 then
      rollback;
    else
      commit;
    end if;
    select o_ret;
end $$
delimiter ;
