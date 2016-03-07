#ifndef __TAF_PATCH_H_
#define __TAF_PATCH_H_

#include "patch/Patch.h"

namespace taf
{
/**
 * patch服务客户端库
 * 采用该库实现从patch服务同步文件到本地
 */

/////////////////////////////////////////////////////////////////////////////////////
/**
 * 下载异常
 */
struct TafPatchException : public TC_Exception
{
	TafPatchException(const string &buffer) : TC_Exception(buffer){};
    TafPatchException(const string &buffer, int err) : TC_Exception(buffer, err){};
	~TafPatchException() throw(){};
};

/**
 * 下载通知接口
 */
class TafPatchNotifyInterface : public TC_HandleBase
{
public:
    /**
     * 删除本地目录
     * @param sDir
     */
    virtual void onRemoveLocalDirectory(const string &sDir) = 0;

    /**
     * 删除本地目录成功
     * @param sDir
     */
    virtual void onRemoveLocalDirectoryOK(const string &sDir) = 0;

    /**
     * 开始获取文件链表
     */
    virtual void onListFile() = 0;

    /**
     * 获取文件链表成功
     * @param vf
     */
    virtual void onListFileOK(const vector<FileInfo> &vf) = 0;

    /**
     * 开始下载
     * @param fi
     */
    virtual void onDownload(const FileInfo &fi) = 0;

    /**
     * 下载文件成功
     * @param fi
     * @param pos
     * @param dest, 保存本地路径
     */
    virtual void onDownloading(const FileInfo &fi, size_t pos, const string &dest) = 0;

    /**
     * 下载文件成功
     * @param fi
     * @param dest, 保存本地路径
     */
    virtual void onDownloadOK(const FileInfo &fi, const string &dest) = 0;

    /**
     * 设置可执行
     * @param fi
     */
    virtual void onSetExecutable(const FileInfo &fi) = 0;

    /**
     * 所有文件列表文件下载成功
     * @param vf
     */
    virtual void onDownloadAllOK(const vector<FileInfo> &vf, time_t timeBegin, time_t timeEnd) = 0;

	/**
     * 上报下载文件所有的时间
     * @param file, beginTime, endTime
     */
	virtual void onReportTime(const string & sFile, const time_t timeBegin, const time_t timeEnd) = 0;
};

typedef TC_AutoPtr<TafPatchNotifyInterface> TafPatchNotifyInterfacePtr;

/**
 * 下载操作类
 */
class TafPatch
{
public:

    /**
     * 构造函数
     */
    TafPatch();

    /**
     * 初始化
     * @param _patchPrx, patch服务器地址
     * @param remote_dir, 远程同步目录, 不能有..符号
     * @param local_dir, 同步到本地的目录
     */
    void init(const PatchPrx &patchPrx, const string &remote_dir, const string &local_dir, const bool bCheck = true);

    /**
     * 设置是否删除本地目录
     * @param bRemove
     */
    void setRemove(bool bRemove);

    /**
     * 下载, 失败抛出异常
     *
     */
    void download(const TafPatchNotifyInterfacePtr &pPtr);


	/**
	 * 下载绝对路径的文件
	 * 
	 * @author kevintian (2010-8-6)
	 * 
	 * @param pPtr 
	 */
	void downloadSubborn(const TafPatchNotifyInterfacePtr &pPtr);


protected:

    /**
     * 下载某一个文件
     * @param fi
     */
    void download(bool bDir, const FileInfo &fi, const TafPatchNotifyInterfacePtr &pPtr);


	/**
	 * 下载绝对路径下的一个文件
	 * 
	 * @author kevintian (2010-8-6)
	 * 
	 * @param sTmpPth 
	 * @param bDir 
	 * @param fi 
	 * @param pPtr 
	 */
	void downloadSubborn(const string & sTmpPth, bool bDir, const FileInfo & fi, const TafPatchNotifyInterfacePtr & pPtr);

    /**
     * 检查本地路径
     */
    void checkLocalDir();

protected:

    /**
     * 远程地址
     */
    string          _remote_dir;

    /**
     * 本地地址
     */
    string          _local_dir;

    /**
     * 是否删除本地同步目录
     */
    bool            _bRemove;

    /**
     * patch服务器
     */
    PatchPrx        _patchPrx;
};

}

#endif


