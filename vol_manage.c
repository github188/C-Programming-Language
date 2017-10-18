__s32 vol_get_size(char * vol_path, __u64 * total_size, __u64 * free_size)
{
    int ret;
    char cmd[MAX_SHELL_STR_LEN] = {0};
    char temp_path[PATH_NAME_LEN] = {0};
    int fd; 
    FILE * file_temp = NULL;
    char * str = NULL;                                                      //解析字符串的临时变量
    char * strs[6] = {0};                                                   //保存解析后的字符串
    int i = 0;                                                              //解析字符串时使用
    char parse_buf[PHASE_LINE_LEN] = {0};
    struct statfs vol_statfs;
    time_t temp_time;
    char mount_point[PATH_NAME_LEN] = {0};

    fd = open(vol_path, O_RDONLY);
    if (-1 == fd) {
        log_write(LOG_ERR, "open vol %s failed.", vol_path);
        return -1;
    }
    off_t off = lseek(fd, 0, SEEK_END);                                     //获取总大小
    *total_size = off;
    ret = is_logical_volume(vol_path);
    if (1 == ret) {
        strncpy(temp_path, vol_path, PATH_NAME_LEN);
        logical_convert_combination(temp_path);
        snprintf(cmd, MAX_SHELL_STR_LEN, "mount -l | grep %s", temp_path);        
    } else if (0 == ret) {
        snprintf(cmd, MAX_SHELL_STR_LEN, "mount -l | grep %s", vol_path);
    } else {
        log_write(LOG_ERR, "the vol_path %s is illegal.", vol_path);
        return -1;
    }
    log_write(LOG_INFO, "cmd:%s",cmd);  
    file_temp = popen(cmd, "r");
    if (NULL == file_temp) {
        perror("pipe open failed");
        return -1;
    }
    
    if(NULL != fgets(parse_buf, PHASE_LINE_LEN, file_temp)) {
        str = parse_buf;
        while(NULL != (strs[i] = strtok(str," "))){
            i++;
            str = NULL;
        }
        statfs(strs[2], &vol_statfs);
        //*total_size = vol_statfs.f_blocks * vol_statfs.f_bsize;
        *free_size = vol_statfs.f_bfree  * vol_statfs.f_bsize;
        goto out;
    } else {                                                                                          //如果没有挂载，则创建一个挂载点
        time(&temp_time);
        snprintf(mount_point, PATH_NAME_LEN, "/mnt/%d", (int)temp_time);
        snprintf(cmd, MAX_SHELL_STR_LEN, "mkdir %s && mount %s %s 2>&1", mount_point, vol_path, mount_point);
        file_temp = popen(cmd, "r");
        //snprintf(mount_fail, PHASE_LINE_LEN, "mount: you must specify the filesystem type");
        if (NULL == file_temp) {
            perror("pipe open failed");
            return -1;
        }
        if (NULL != fgets(parse_buf, PHASE_LINE_LEN, file_temp)) {                                    //这里默认处理为卷没有格式化
            //log_write(LOG_INFO, "%s", parse_buf);
            *free_size = off;
            snprintf(cmd, MAX_SHELL_STR_LEN, "rm -rf %s", mount_point);
            exec_cmd(cmd, &ret, NULL, NULL); 
            goto out;
        } else {
            log_write(LOG_INFO, "%s", parse_buf);
            statfs(mount_point, &vol_statfs);
            *free_size = vol_statfs.f_bfree  * vol_statfs.f_bsize;
            
            if(0 == vol_unmount(vol_path)) {
                snprintf(cmd, MAX_SHELL_STR_LEN, "rm -rf %s", mount_point);
                exec_cmd(cmd, &ret, NULL, NULL); 
                goto out;
            }
        }
    }
    if (ferror(file_temp)) {
        perror("pipe read failed");
        return -1;
    }
    out:
    pclose(file_temp);
    return 0;
}
