#include <libidmef/idmef.h>
#include <string.h>

int main(){
    FILE *file;
    int ret;
    prelude_io_t *pio;
    idmef_message_t *idmef, *idmef_heartbeat;
    idmef_alert_t *alert;
    idmef_heartbeat_t *heartbeat;
    idmef_classification_t *class;
    prelude_string_t *str;
    idmef_time_t * time;

    file = fopen("/tmp/example.idmef", "a");

    prelude_io_new(&pio);
    prelude_io_set_file_io(pio, file);

    ret = idmef_message_new(&idmef);
    if ( ret < 0 ) {
            prelude_perror(ret, "unable to create IDMEF message");
            return -1;
    }
    ret = idmef_message_new_alert(idmef, &alert);
    if ( ret < 0 ) {
            prelude_perror(ret, "unable to create IDMEF alert");
            idmef_message_destroy(idmef);
            return -1;
    }

    ret = idmef_message_new(&idmef_heartbeat);
    if ( ret < 0 ) {
            prelude_perror(ret, "unable to create IDMEF message");
            return -1;
    }
    ret = idmef_message_new_heartbeat(idmef_heartbeat, &heartbeat);
    if ( ret < 0 ) {
            prelude_perror(ret, "unable to create IDMEF alert");
            idmef_message_destroy(idmef_heartbeat);
            return -1;
    }

    idmef_message_set_string(idmef_heartbeat, "heartbeat.messageid", "superid");
    idmef_message_set_string(idmef_heartbeat, "heartbeat.heartbeat_interval", "66666");
    idmef_message_set_string(idmef_heartbeat, "heartbeat.analyzer(0).analyzerid", "example.idmef");
    idmef_message_set_string(idmef_heartbeat, "heartbeat.analyzer(0).name", "example.idmef");
    idmef_message_set_string(idmef_heartbeat, "heartbeat.analyzer(0).manufacturer", "example.idmef");
    idmef_message_set_string(idmef_heartbeat, "heartbeat.analyzer(0).model", "example.idmef");
    idmef_message_set_string(idmef_heartbeat, "heartbeat.analyzer(0).version", "example.idmef");
    idmef_message_set_string(idmef_heartbeat, "heartbeat.analyzer(0).class", "example.idmef");
    idmef_message_set_string(idmef_heartbeat, "heartbeat.analyzer(0).ostype", "example.idmef");
    idmef_message_set_string(idmef_heartbeat, "heartbeat.analyzer(0).osversion", "example.idmef");



    idmef_message_set_string(idmef, "alert.messageid", "superid");
    idmef_message_set_string(idmef, "alert.classification.ident", "OSVDB-XXXX");
    idmef_message_set_string(idmef, "alert.classification.text", "OSVDB-XXXX");
    idmef_message_set_string(idmef, "alert.classification.reference(0).name", "OSVDB-XXXX");
    idmef_message_set_string(idmef, "alert.classification.reference(0).origin", "osvdb");
    idmef_message_set_string(idmef, "alert.classification.reference(0).url", "http://my.url/");
    idmef_message_set_string(idmef, "alert.target(0).node.address(0).address", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).node.address(0).category", "ipv4-addr");
    idmef_message_set_string(idmef, "alert.analyzer(0).analyzerid", "example.idmef");
    idmef_message_set_string(idmef, "alert.analyzer(0).name", "example.idmef");
    idmef_message_set_string(idmef, "alert.analyzer(0).manufacturer", "example.idmef");
    idmef_message_set_string(idmef, "alert.analyzer(0).model", "example.idmef");
    idmef_message_set_string(idmef, "alert.analyzer(0).version", "example.idmef");
    idmef_message_set_string(idmef, "alert.analyzer(0).class", "example.idmef");
    idmef_message_set_string(idmef, "alert.analyzer(0).ostype", "example.idmef");
    idmef_message_set_string(idmef, "alert.analyzer(0).osversion", "example.idmef");

    idmef_message_set_string(idmef, "alert.analyzer(0).node.ident", "example.idmef");
    idmef_message_set_string(idmef, "alert.analyzer(0).node.category", "dns");

    idmef_message_set_string(idmef, "alert.analyzer(0).node.location", "example.idmef");
    idmef_message_set_string(idmef, "alert.analyzer(0).node.name", "example.idmef");

    idmef_message_set_string(idmef, "alert.analyzer(0).node.address(0).ident", "example.idmef");
    idmef_message_set_string(idmef, "alert.analyzer(0).node.address(0).category", "ipv4-addr");
    idmef_message_set_string(idmef, "alert.analyzer(0).node.address(0).vlan_name", "example.idmef");
    idmef_message_set_string(idmef, "alert.analyzer(0).node.address(0).vlan_num", "5");
    idmef_message_set_string(idmef, "alert.analyzer(0).node.address(0).address", "example.idmef");
    idmef_message_set_string(idmef, "alert.analyzer(0).node.address(0).netmask", "example.idmef");

    idmef_message_set_string(idmef, "alert.analyzer(0).node.address(1).ident", "ezf");
    idmef_message_set_string(idmef, "alert.analyzer(0).node.address(1).category", "ipv4-addr");
    idmef_message_set_string(idmef, "alert.analyzer(0).node.address(1).vlan_name", "ezffez");
    idmef_message_set_string(idmef, "alert.analyzer(0).node.address(1).vlan_num", "12");
    idmef_message_set_string(idmef, "alert.analyzer(0).node.address(1).address", "zefez");
    idmef_message_set_string(idmef, "alert.analyzer(0).node.address(1).netmask", "zefez");
    idmef_message_set_string(idmef, "alert.analyzer(0).process.ident", "example.idmef");
    idmef_message_set_string(idmef, "alert.analyzer(0).process.name", "example.idmef");
    idmef_message_set_string(idmef, "alert.analyzer(0).process.pid", "666");
    idmef_message_set_string(idmef, "alert.analyzer(0).process.path", "example.idmef");
    idmef_message_set_string(idmef, "alert.analyzer(0).process.arg(0)", "example.idmef");
    idmef_message_set_string(idmef, "alert.analyzer(0).process.arg(1)", "gumi");
    idmef_message_set_string(idmef, "alert.analyzer(0).process.env(0)", "example.idmef");


    idmef_message_set_string(idmef, "alert.source(0).ident", "source style");
    idmef_message_set_string(idmef, "alert.source(0).spoofed", "yes");
    idmef_message_set_string(idmef, "alert.source(0).interface", "eth5");
    idmef_message_set_string(idmef, "alert.source(0).node.ident", "example.idmef");
    idmef_message_set_string(idmef, "alert.source(0).node.category", "dns");

    idmef_message_set_string(idmef, "alert.source(0).node.location", "example.idmef");
    idmef_message_set_string(idmef, "alert.source(0).node.name", "example.idmef");

    idmef_message_set_string(idmef, "alert.source(0).node.address(0).ident", "example.idmef");
    idmef_message_set_string(idmef, "alert.source(0).node.address(0).category", "ipv4-addr");
    idmef_message_set_string(idmef, "alert.source(0).node.address(0).vlan_name", "example.idmef");
    idmef_message_set_string(idmef, "alert.source(0).node.address(0).vlan_num", "5");
    idmef_message_set_string(idmef, "alert.source(0).node.address(0).address", "example.idmef");
    idmef_message_set_string(idmef, "alert.source(0).node.address(0).netmask", "example.idmef");

    idmef_message_set_string(idmef, "alert.source(0).node.address(1).ident", "ezf");
    idmef_message_set_string(idmef, "alert.source(0).node.address(1).category", "ipv4-addr");
    idmef_message_set_string(idmef, "alert.source(0).node.address(1).vlan_name", "ezffez");
    idmef_message_set_string(idmef, "alert.source(0).node.address(1).vlan_num", "12");
    idmef_message_set_string(idmef, "alert.source(0).node.address(1).address", "zefez");
    idmef_message_set_string(idmef, "alert.source(0).node.address(1).netmask", "zefez");
    idmef_message_set_string(idmef, "alert.source(0).process.ident", "example.idmef");
    idmef_message_set_string(idmef, "alert.source(0).process.name", "example.idmef");
    idmef_message_set_string(idmef, "alert.source(0).process.pid", "666");
    idmef_message_set_string(idmef, "alert.source(0).process.path", "example.idmef");
    idmef_message_set_string(idmef, "alert.source(0).process.arg(0)", "example.idmef");
    idmef_message_set_string(idmef, "alert.source(0).process.arg(1)", "gumi");
    idmef_message_set_string(idmef, "alert.source(0).process.env(0)", "example.idmef");

    idmef_message_set_string(idmef, "alert.source(0).service.ident", "example");
    idmef_message_set_string(idmef, "alert.source(0).service.ip_version", "6");
    idmef_message_set_string(idmef, "alert.source(0).service.iana_protocol_number", "example");
    idmef_message_set_string(idmef, "alert.source(0).service.iana_protocol_name", "6");
    idmef_message_set_string(idmef, "alert.source(0).service.name", "example");
    idmef_message_set_string(idmef, "alert.source(0).service.port", "6");
    idmef_message_set_string(idmef, "alert.source(0).service.portlist", "example");
    idmef_message_set_string(idmef, "alert.source(0).service.protocol", "example");

    idmef_message_set_string(idmef, "alert.source(0).service.web_service.url", "example");
    idmef_message_set_string(idmef, "alert.source(0).service.web_service.cgi", "example");
    idmef_message_set_string(idmef, "alert.source(0).service.web_service.http_method", "example");
    idmef_message_set_string(idmef, "alert.source(0).service.web_service.arg(0)", "super argument");
    idmef_message_set_string(idmef, "alert.source(0).service.web_service.arg(1)", "MEGA ARGUMENT");

    idmef_message_set_string(idmef, "alert.target(0).ident", "target style");
    idmef_message_set_string(idmef, "alert.target(0).spoofed", "yes");
    idmef_message_set_string(idmef, "alert.target(0).interface", "eth2");
    idmef_message_set_string(idmef, "alert.target(0).node.ident", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).node.category", "dns");

    idmef_message_set_string(idmef, "alert.target(0).node.location", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).node.name", "example.idmef");

    idmef_message_set_string(idmef, "alert.target(0).node.address(0).ident", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).node.address(0).category", "ipv4-addr");
    idmef_message_set_string(idmef, "alert.target(0).node.address(0).vlan_name", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).node.address(0).vlan_num", "5");
    idmef_message_set_string(idmef, "alert.target(0).node.address(0).address", "192.168.2.50");
    idmef_message_set_string(idmef, "alert.target(0).node.address(0).netmask", "example.idmef");

    idmef_message_set_string(idmef, "alert.target(0).node.address(1).ident", "ezf");
    idmef_message_set_string(idmef, "alert.target(0).node.address(1).category", "ipv4-addr");
    idmef_message_set_string(idmef, "alert.target(0).node.address(1).vlan_name", "ezffez");
    idmef_message_set_string(idmef, "alert.target(0).node.address(1).vlan_num", "12");
    idmef_message_set_string(idmef, "alert.target(0).node.address(1).address", "zefez");
    idmef_message_set_string(idmef, "alert.target(0).node.address(1).netmask", "zefez");
    idmef_message_set_string(idmef, "alert.target(0).process.ident", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).process.name", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).process.pid", "666");
    idmef_message_set_string(idmef, "alert.target(0).process.path", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).process.arg(0)", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).process.arg(1)", "gumi");
    idmef_message_set_string(idmef, "alert.target(0).process.env(0)", "example.idmef");


    idmef_message_set_string(idmef, "alert.target(0).service.ident", "example");
    idmef_message_set_string(idmef, "alert.target(0).service.ip_version", "6");
    idmef_message_set_string(idmef, "alert.target(0).service.iana_protocol_number", "example");
    idmef_message_set_string(idmef, "alert.target(0).service.iana_protocol_name", "6");
    idmef_message_set_string(idmef, "alert.target(0).service.name", "example");
    idmef_message_set_string(idmef, "alert.target(0).service.port", "6");
    idmef_message_set_string(idmef, "alert.target(0).service.portlist", "example");
    idmef_message_set_string(idmef, "alert.target(0).service.protocol", "example");

    idmef_message_set_string(idmef, "alert.target(0).service.snmp_service.oid", "example");
    idmef_message_set_string(idmef, "alert.target(0).service.snmp_service.message_processing_model", "6");
    idmef_message_set_string(idmef, "alert.target(0).service.snmp_service.security_model", "example");
    idmef_message_set_string(idmef, "alert.target(0).service.snmp_service.security_name", "example");
    idmef_message_set_string(idmef, "alert.target(0).service.snmp_service.security_level", "6");
    idmef_message_set_string(idmef, "alert.target(0).service.snmp_service.context_name", "example");
    idmef_message_set_string(idmef, "alert.target(0).service.snmp_service.context_engine_id", "example");
    idmef_message_set_string(idmef, "alert.target(0).service.snmp_service.command", "example");
    idmef_message_set_string(idmef, "alert.target(0).service.snmp_service.community", "example");


    idmef_message_set_string(idmef, "alert.target(0).file(0).ident", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).file(0).name", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).file(0).path", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).file(0).data_size", "6");
    idmef_message_set_string(idmef, "alert.target(0).file(0).disk_size", "6");

    idmef_message_set_string(idmef, "alert.target(0).file(0).file_access(0).permission(0)", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).file(0).file_access(0).permission(1)", "example.idmef");

    idmef_message_set_string(idmef, "alert.target(0).file(0).file_access(0).user_id(0).ident", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).file(0).file_access(0).user_id(0).type", "target-user");
    idmef_message_set_string(idmef, "alert.target(0).file(0).file_access(0).user_id(0).tty", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).file(0).file_access(0).user_id(0).name", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).file(0).file_access(0).user_id(0).number", "6");

    idmef_message_set_string(idmef, "alert.target(0).file(0).linkage(0).category", "stream");
    idmef_message_set_string(idmef, "alert.target(0).file(0).linkage(0).name", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).file(0).linkage(0).path", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).file(0).linkage(0).file.name", "example.idmef dans linkage");

    idmef_message_set_string(idmef, "alert.target(0).file(0).inode.number", "6");
    idmef_message_set_string(idmef, "alert.target(0).file(0).inode.major_device", "6");
    idmef_message_set_string(idmef, "alert.target(0).file(0).inode.minor_device", "6");
    idmef_message_set_string(idmef, "alert.target(0).file(0).inode.c_major_device", "6");
    idmef_message_set_string(idmef, "alert.target(0).file(0).inode.c_minor_device", "6");

    idmef_message_set_string(idmef, "alert.target(0).file(0).checksum.value", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).file(0).checksum.key", "example.idmef");
    idmef_message_set_string(idmef, "alert.target(0).file(0).checksum.algorithm", "md5");

    idmef_message_set_string(idmef, "alert.target(0).file(0).category", "current");
    idmef_message_set_string(idmef, "alert.target(0).file(0).fstype", "ufs");
    idmef_message_set_string(idmef, "alert.target(0).file(0).file_type", "example.idmef");


    idmef_message_set_string(idmef, "alert.assessment.impact.severity", "high");
    idmef_message_set_string(idmef, "alert.assessment.impact.completion", "failed");
    idmef_message_set_string(idmef, "alert.assessment.impact.type", "dos");
    idmef_message_set_string(idmef, "alert.assessment.impact.description", "example.idmef");

    idmef_message_set_string(idmef, "alert.assessment.action(0).category", "other");
    idmef_message_set_string(idmef, "alert.assessment.action(0).description", "example.idmef");

    idmef_message_set_string(idmef, "alert.assessment.confidence.rating", "high");
    idmef_message_set_string(idmef, "alert.assessment.confidence.confidence", "5.4");


    idmef_message_set_string(idmef, "alert.tool_alert.name", "example.idmef");
    idmef_message_set_string(idmef, "alert.tool_alert.command", "example.idmef");

    idmef_message_set_string(idmef, "alert.tool_alert.alertident(0).alertident", "ident de l'alerte");
    idmef_message_set_string(idmef, "alert.tool_alert.alertident(0).analyzerid", "superanalze");
    idmef_message_set_string(idmef, "alert.tool_alert.alertident(1).alertident", "ident de la deuxieme alerte");
    idmef_message_set_string(idmef, "alert.tool_alert.alertident(1).analyzerid", "superanalze");

    idmef_message_set_string(idmef, "alert.additional_data(0).meaning", "additional1");
    idmef_message_set_string(idmef, "alert.additional_data(0).data", "value de l'additional data 1");

    idmef_message_set_string(idmef, "alert.additional_data(1).meaning", "additional2");
    idmef_message_set_string(idmef, "alert.additional_data(1).data", "value de l'additional data 2");

    idmef_time_new_from_gettimeofday(&time);
    idmef_alert_set_detect_time(alert, time);
    idmef_alert_set_analyzer_time(alert, time);

    idmef_heartbeat_set_analyzer_time(heartbeat, time);

    idmef_message_new_version(idmef_heartbeat, &str);
    prelude_string_set_constant(str, "1.0");

    idmef_message_new_version(idmef, &str);
    prelude_string_set_constant(str, "1.0");

    idmef_message_print(idmef, pio);
    idmef_message_write(idmef, pio);
}


