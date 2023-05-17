branch_list = []
history_list = []
change_log = []

BRANCH_ID = 0
BRANCH_NAME = 1
BRANCH_ORIGIN_ID = 2
BRANCH_UPDATE_TIME = 3

activated_branch = 0

import subprocess

def command(param, split = 0):
    param = ["flow"] + param
    startupinfo = subprocess.STARTUPINFO()
    startupinfo.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    proc = subprocess.Popen(param, stdout=subprocess.PIPE, stdin=subprocess.PIPE)
    proc.wait()
    if split:
        raw = str(proc.stdout.read().decode('utf-8'))
        ret = []
        data = raw.split('\r\n')
        while len(data) % split: data.pop()
        for i in range(0, len(data), split):
            sub = []
            for j in range(0, split):
                sub.append(data[i + j])
            ret.append(sub)
        return ret, proc.returncode
    return proc.returncode
