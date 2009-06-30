--Beginning of script 1--   DatabaseDB2LUOW (SEG6_LLO) [WARNING***Please do not alter this line]--
-- CONNECT TO SEG6_LLO USER XXXX using XXXX;
CREATE TABLESPACE QCASN3 MANAGED BY SYSTEM USING ('QCASN3_TSC');
CREATE TABLE ASN.IBMQREP_CAPPARMS
(
 QMGR VARCHAR(48) NOT NULL,
 REMOTE_SRC_SERVER VARCHAR(18),
 RESTARTQ VARCHAR(48) NOT NULL,
 ADMINQ VARCHAR(48) NOT NULL,
 STARTMODE VARCHAR(6) NOT NULL WITH DEFAULT 'WARMSI',
 MEMORY_LIMIT INTEGER NOT NULL WITH DEFAULT 500,
 COMMIT_INTERVAL INTEGER NOT NULL WITH DEFAULT 500,
 AUTOSTOP CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 MONITOR_INTERVAL INTEGER NOT NULL WITH DEFAULT 300000,
 MONITOR_LIMIT INTEGER NOT NULL WITH DEFAULT 10080,
 TRACE_LIMIT INTEGER NOT NULL WITH DEFAULT 10080,
 SIGNAL_LIMIT INTEGER NOT NULL WITH DEFAULT 10080,
 PRUNE_INTERVAL INTEGER NOT NULL WITH DEFAULT 300,
 SLEEP_INTERVAL INTEGER NOT NULL WITH DEFAULT 5000,
 LOGREUSE CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 LOGSTDOUT CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 TERM CHARACTER(1) NOT NULL WITH DEFAULT 'Y',
 CAPTURE_PATH VARCHAR(1040) WITH DEFAULT NULL,
 ARCH_LEVEL CHARACTER(4) NOT NULL WITH DEFAULT '0905',
 COMPATIBILITY CHARACTER(4) NOT NULL WITH DEFAULT '0905',
 LOB_SEND_OPTION CHARACTER(1) NOT NULL WITH DEFAULT 'I',
 QFULL_NUM_RETRIES INTEGER NOT NULL WITH DEFAULT 30,
 QFULL_RETRY_DELAY INTEGER NOT NULL WITH DEFAULT 250
)
 IN QCASN3;
ALTER TABLE ASN.IBMQREP_CAPPARMS
 VOLATILE CARDINALITY;
CREATE UNIQUE INDEX ASN.IX1CQMGRCOL ON ASN.IBMQREP_CAPPARMS
(
 QMGR ASC
);
CREATE TABLE ASN.IBMQREP_SENDQUEUES
(
 PUBQMAPNAME VARCHAR(128) NOT NULL,
 SENDQ VARCHAR(48) NOT NULL,
 RECVQ VARCHAR(48),
 MESSAGE_FORMAT CHARACTER(1) NOT NULL WITH DEFAULT 'C',
 MSG_CONTENT_TYPE CHARACTER(1) NOT NULL WITH DEFAULT 'T',
 STATE CHARACTER(1) NOT NULL WITH DEFAULT 'A',
 STATE_TIME TIMESTAMP NOT NULL WITH DEFAULT CURRENT TIMESTAMP,
 STATE_INFO CHARACTER(8),
 ERROR_ACTION CHARACTER(1) NOT NULL WITH DEFAULT 'S',
 HEARTBEAT_INTERVAL INTEGER NOT NULL WITH DEFAULT 60,
 MAX_MESSAGE_SIZE INTEGER NOT NULL WITH DEFAULT 64,
 APPLY_SERVER VARCHAR(18),
 APPLY_ALIAS VARCHAR(8),
 APPLY_SCHEMA VARCHAR(128),
 DESCRIPTION VARCHAR(254),
 MESSAGE_CODEPAGE INTEGER,
 COLUMN_DELIMITER CHARACTER(1),
 STRING_DELIMITER CHARACTER(1),
 RECORD_DELIMITER CHARACTER(1),
 DECIMAL_POINT CHARACTER(1),
 SENDRAW_IFERROR CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 PRIMARY KEY(SENDQ)
)
 IN QCASN3;
ALTER TABLE ASN.IBMQREP_SENDQUEUES
 VOLATILE CARDINALITY;
CREATE UNIQUE INDEX ASN.IX1PUBMAPCOL ON ASN.IBMQREP_SENDQUEUES
(
 PUBQMAPNAME ASC
);
CREATE TABLE ASN.IBMQREP_SUBS
(
 SUBNAME VARCHAR(132) NOT NULL,
 SOURCE_OWNER VARCHAR(128) NOT NULL,
 SOURCE_NAME VARCHAR(128) NOT NULL,
 TARGET_SERVER VARCHAR(18),
 TARGET_ALIAS VARCHAR(8),
 TARGET_OWNER VARCHAR(128),
 TARGET_NAME VARCHAR(128),
 TARGET_TYPE INTEGER,
 APPLY_SCHEMA VARCHAR(128),
 SENDQ VARCHAR(48) NOT NULL,
 SEARCH_CONDITION VARCHAR(2048) WITH DEFAULT NULL,
 SUB_ID INTEGER WITH DEFAULT NULL,
 SUBTYPE CHARACTER(1) NOT NULL WITH DEFAULT 'U',
 ALL_CHANGED_ROWS CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 BEFORE_VALUES CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 CHANGED_COLS_ONLY CHARACTER(1) NOT NULL WITH DEFAULT 'Y',
 HAS_LOADPHASE CHARACTER(1) NOT NULL WITH DEFAULT 'I',
 STATE CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 STATE_TIME TIMESTAMP NOT NULL WITH DEFAULT CURRENT TIMESTAMP,
 STATE_INFO CHARACTER(8),
 STATE_TRANSITION VARCHAR(256) FOR BIT DATA,
 SUBGROUP VARCHAR(30) WITH DEFAULT NULL,
 SOURCE_NODE SMALLINT NOT NULL WITH DEFAULT 0,
 TARGET_NODE SMALLINT NOT NULL WITH DEFAULT 0,
 GROUP_MEMBERS CHARACTER(254) FOR BIT DATA WITH DEFAULT NULL,
 OPTIONS_FLAG CHARACTER(4) NOT NULL WITH DEFAULT 'NNNN',
 SUPPRESS_DELETES CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 DESCRIPTION VARCHAR(200),
 TOPIC VARCHAR(256),
 PRIMARY KEY(SUBNAME),
 CONSTRAINT FKSENDQ FOREIGN KEY(SENDQ) REFERENCES
 ASN.IBMQREP_SENDQUEUES(SENDQ)
)
 IN QCASN3;
ALTER TABLE ASN.IBMQREP_SUBS
 VOLATILE CARDINALITY;
CREATE TABLE ASN.IBMQREP_SRC_COLS
(
 SUBNAME VARCHAR(132) NOT NULL,
 SRC_COLNAME VARCHAR(128) NOT NULL,
 IS_KEY SMALLINT NOT NULL WITH DEFAULT 0,
 COL_OPTIONS_FLAG CHARACTER(10) NOT NULL WITH DEFAULT 'NNNNNNNNNN',
 PRIMARY KEY(SUBNAME, SRC_COLNAME),
 CONSTRAINT FKSUBS FOREIGN KEY(SUBNAME) REFERENCES ASN.IBMQREP_SUBS
(SUBNAME)
)
 IN QCASN3;
ALTER TABLE ASN.IBMQREP_SRC_COLS
 VOLATILE CARDINALITY;
CREATE TABLE ASN.IBMQREP_SRCH_COND
(
 ASNQREQD INTEGER
)
 IN QCASN3;
CREATE TABLE ASN.IBMQREP_SIGNAL
(
 SIGNAL_TIME TIMESTAMP NOT NULL WITH DEFAULT CURRENT TIMESTAMP,
 SIGNAL_TYPE VARCHAR(30) NOT NULL,
 SIGNAL_SUBTYPE VARCHAR(30),
 SIGNAL_INPUT_IN VARCHAR(500),
 SIGNAL_STATE CHARACTER(1) NOT NULL WITH DEFAULT 'P',
 SIGNAL_LSN CHARACTER(10) FOR BIT DATA
)
 DATA CAPTURE CHANGES
 IN QCASN3;
ALTER TABLE ASN.IBMQREP_SIGNAL
 VOLATILE CARDINALITY;
CREATE TABLE ASN.IBMQREP_CAPTRACE
(
 OPERATION CHARACTER(8) NOT NULL,
 TRACE_TIME TIMESTAMP NOT NULL,
 DESCRIPTION VARCHAR(1024) NOT NULL,
 REASON_CODE INTEGER,
 MQ_CODE INTEGER
)
 IN QCASN3;
CREATE TABLE ASN.IBMQREP_CAPMON
(
 MONITOR_TIME TIMESTAMP NOT NULL,
 CURRENT_LOG_TIME TIMESTAMP NOT NULL,
 CAPTURE_IDLE INTEGER NOT NULL,
 CURRENT_MEMORY INTEGER NOT NULL,
 ROWS_PROCESSED INTEGER NOT NULL,
 TRANS_SKIPPED INTEGER NOT NULL,
 TRANS_PROCESSED INTEGER NOT NULL,
 TRANS_SPILLED INTEGER NOT NULL,
 MAX_TRANS_SIZE INTEGER NOT NULL,
 QUEUES_IN_ERROR INTEGER NOT NULL,
 RESTART_SEQ CHARACTER(10) FOR BIT DATA NOT NULL,
 CURRENT_SEQ CHARACTER(10) FOR BIT DATA NOT NULL,
 LAST_EOL_TIME TIMESTAMP,
 PRIMARY KEY(MONITOR_TIME)
)
 IN QCASN3;
ALTER TABLE ASN.IBMQREP_CAPMON
 VOLATILE CARDINALITY;
CREATE TABLE ASN.IBMQREP_CAPQMON
(
 MONITOR_TIME TIMESTAMP NOT NULL,
 SENDQ VARCHAR(48) NOT NULL,
 ROWS_PUBLISHED INTEGER NOT NULL,
 TRANS_PUBLISHED INTEGER NOT NULL,
 CHG_ROWS_SKIPPED INTEGER NOT NULL,
 DELROWS_SUPPRESSED INTEGER NOT NULL,
 ROWS_SKIPPED INTEGER NOT NULL,
 QFULL_ERROR_COUNT INTEGER NOT NULL,
 LOBS_TOO_BIG INTEGER NOT NULL WITH DEFAULT 0,
 XMLDOCS_TOO_BIG INTEGER NOT NULL WITH DEFAULT 0,
 PRIMARY KEY(MONITOR_TIME, SENDQ)
)
 IN QCASN3;
ALTER TABLE ASN.IBMQREP_CAPQMON
 VOLATILE CARDINALITY;
CREATE TABLE ASN.IBMQREP_CAPENQ
(
 LOCKNAME INTEGER
)
 IN QCASN3;
CREATE TABLE ASN.IBMQREP_ADMINMSG
(
 MQMSGID CHARACTER(24) FOR BIT DATA NOT NULL,
 MSG_TIME TIMESTAMP NOT NULL WITH DEFAULT CURRENT TIMESTAMP,
 PRIMARY KEY(MQMSGID)
)
 IN QCASN3;
ALTER TABLE ASN.IBMQREP_ADMINMSG
 VOLATILE CARDINALITY;
CREATE TABLE ASN.IBMQREP_IGNTRAN
(
 AUTHID CHARACTER(128),
 AUTHTOKEN CHARACTER(30),
 PLANNAME CHARACTER(8),
 IGNTRANTRC CHARACTER(1) NOT NULL WITH DEFAULT 'Y'
)
 IN QCASN3;
CREATE TABLE ASN.IBMQREP_IGNTRANTRC
(
 IGNTRAN_TIME TIMESTAMP NOT NULL WITH DEFAULT CURRENT TIMESTAMP,
 AUTHID CHARACTER(128),
 AUTHTOKEN CHARACTER(30),
 PLANNAME CHARACTER(8),
 TRANSID CHARACTER(10) FOR BIT DATA NOT NULL,
 COMMITLSN CHARACTER(10) FOR BIT DATA NOT NULL
)
 IN QCASN3;
CREATE TABLE ASN.IBMQREP_CAPENVINFO
(
 NAME VARCHAR(30) NOT NULL,
 VALUE VARCHAR(3800)
)
 IN QCASN3;
INSERT INTO ASN.IBMQREP_CAPPARMS
 (qmgr, restartq, adminq, startmode, memory_limit, commit_interval,
 autostop, monitor_interval, monitor_limit, trace_limit, signal_limit,
 prune_interval, sleep_interval, logreuse, logstdout, term, arch_level
, compatibility)
 VALUES
 ('QM2', 'ASN.QM2.RESTARTQ', 'ASN.QM2.ADMINQ', 'WARMSI', 500, 500, 'N'
, 300000, 10080, 10080, 10080, 300, 5000, 'N', 'N', 'Y', '0905',
 '0905');
-- COMMIT;
