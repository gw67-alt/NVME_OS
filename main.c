#include "nvme.h"

int main(int argc, char **argv) {
    struct nvme_dev *dev;
    int err;
    struct nvme_id_ns ns;
    __u32 nsid;

    // Initialize the NVMe device
    err = parse_and_open(&dev, argc, argv, "Create Namespace", NULL);
    if (err) {
        fprintf(stderr, "Failed to open NVMe device: %s\n", nvme_strerror(err));
        return err;
    }

    // Set namespace parameters
    ns.nsze = cpu_to_le64(1024); // Set namespace size
    ns.ncap = cpu_to_le64(1024); // Set namespace capacity
    ns.flbas = 0; // Set formatted LBA size

    // Create the namespace
    err = nvme_cli_ns_mgmt_create(dev, &ns, &nsid, 120000, 0);
    if (err) {
        fprintf(stderr, "Failed to create namespace: %s\n", nvme_strerror(err));
        dev_close(dev);
        return err;
    }

    printf("Namespace created with ID: %u\n", nsid);

    // Close the NVMe device
    dev_close(dev);
    return 0;
}
