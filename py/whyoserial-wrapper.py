import subprocess
import base64
import json

class WHYsoserialCpp:
    """
    Python wrapper for whysoserial-cpp
    Facilitates integration into pentesting tools
    """

    def __init__(self, binary_path="./whysoserial-cpp"):
        self.binary_path = binary_path

    def generate_payload(self, payload_type, command):
        """
        Generates a payload and returns the data in different formats
        """
        try:
            # Run whysoserial-cpp
            result = subprocess.run(
                [self.binary_path, payload_type, command],
                capture_output=True,
                text=True,
                check=True
            )

            # Parse output
            lines = result.stdout.split('\n')

            payload_data = {
                'type': payload_type,
                'command': command,
                'size': 0,
                'base64': '',
                'hex': '',
                'file': f'{payload_type}_payload.ser'
            }

            # Extract information from output
            for i, line in enumerate(lines):
                if 'Tamaño:' in line:
                    payload_data['size'] = int(line.split()[1])
                elif line.strip() == "Base64:":
                    payload_data['base64'] = lines[i+1].strip()
                elif line.strip() == "Hex:":
                    payload_data['hex'] = lines[i+1].strip()

            return payload_data

        except subprocess.CalledProcessError as e:
            raise Exception(f"Error generating payload: {e.stderr}")

    def generate_for_burp(self, payload_type, command):
        """
        Generates a payload optimized for Burp Suite
        """
        payload = self.generate_payload(payload_type, command)
        return payload['base64']

    def generate_for_curl(self, payload_type, command, url, param_name="data"):
        """
        Generates a ready-to-use curl command
        """
        payload = self.generate_payload(payload_type, command)
        curl_cmd = f'curl -X POST -d "{param_name}={payload["base64"]}" {url}'
        return curl_cmd

    def batch_generate(self, payloads_config):
        """
        Generates multiple payloads according to configuration
        """
        results = []
        for config in payloads_config:
            try:
                payload = self.generate_payload(config['type'], config['command'])
                payload['name'] = config.get('name', f"{config['type']}_{len(results)}")
                results.append(payload)
            except Exception as e:
                print(f"Error in {config}: {e}")

        return results

#

